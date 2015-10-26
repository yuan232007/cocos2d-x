//
//  CocosRuntimeGroup.swift
//  iOSTest
//
//  Created by Rye on 10/22/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

class CocosRuntimeGroup {
	// the right way to write a singleton in swift
    static let sharedInstance = CocosRuntimeGroup()

    var gameInfo: GameInfo?
    var gameConfig: GameConfig?
    var gameManifest: GameManifest?
	var resGroups = [ResGroup]()
	var resGroupsDict = [String: ResGroup]()
    
	func initialize(gameInfo: GameInfo, gameConfig: GameConfig, gameManifest: GameManifest) {
		self.gameInfo = gameInfo
		self.gameConfig = gameConfig
		self.gameManifest = gameManifest
		self.resGroups = getAllResGroups(gameManifest.resourceGroupJSON!)
		self.resGroupsDict = getAllResGroupDict(self.resGroups)
	}

    private func getAllResGroups(json: JSON) -> [ResGroup] {
        var resArray = [ResGroup]()
        for index in 0...json.count - 1 {
            let resGroup = ResGroup(groupInfoMD5:json[index]["group_info_md5"].string,
                					md5: json[index]["md5"].string,
                					priority: json[index]["priority"].int,
                					size: json[index]["size"].int,
                					url: json[index]["url"].string)
            resArray.append(resGroup)
        }
        return resArray
    }

    private func getAllResGroupDict(resGroupArray: [ResGroup]) -> [String: ResGroup] {
    	var resDict = [String: ResGroup]()
    	for group in resGroupArray {
    		resDict[group.name!] = group
    	}
    	return resDict
    }

    func findGroupByName(name: String) -> ResGroup? {
        return self.resGroupsDict[name]
    }

    /**
     * 
     */
    private func isGroupMD5Correct(md5: String?, path: String) -> Bool {
    	if let groupMD5 = md5, fileMD5 = FileUtil.getFileMD5(path) where groupMD5 == fileMD5 {
    		return true
    	}
    	return false
    }

    /**
     * 解压指定分组
     */
    private func unzip(fromPath: String, toPath: String, overwrite: Bool=true) {
        ZipHelper.unzipFileAtPath(fromPath, toDestination: toPath)
    }

    /**
     * 
     */
    private func updateResGroup(gameInfo: GameInfo, resGroup: ResGroup){
        checkResGroup(gameInfo, resGroup: resGroup)
    }
    /**
     * 检查本地 cpk 是否存在, 如果不存在活着 MD5 值不同，则重新下载
     */
    func checkResGroup(gameInfo: GameInfo, resGroup: ResGroup) {
        let localGroupPath = FileUtil.getLocalGroupPath(gameInfo, resGroup: resGroup)
        if isGroupMD5Correct(resGroup.md5, path: localGroupPath) {
            unzip(localGroupPath, toPath: FileUtil.getGameRootPath(gameInfo))
        } else {
            downloadResGroup(gameInfo, resGroup: resGroup)
        }
    }

    /**
     * 下载游戏分组
     */
    func downloadResGroup(gameInfo: GameInfo, resGroup: ResGroup) {
        let fileDownload = FileDownload(urlString: gameInfo.downloadUrl + resGroup.url!, delegate: ResourceGroupDownloadDelegateImpl(cocosRuntimeGroup: self, resGroup: resGroup, gameInfo: gameInfo))
        fileDownload.startDownload()
    }

    /**
     * 下载分组资源回调
     */
    class ResourceGroupDownloadDelegateImpl: FileDownloadAdapter {
        let cocosRuntimeGroup: CocosRuntimeGroup 
        let resGroup: ResGroup
        let gameInfo: GameInfo
        
        init(cocosRuntimeGroup: CocosRuntimeGroup, resGroup: ResGroup, gameInfo: GameInfo) {
            self.cocosRuntimeGroup = cocosRuntimeGroup
            self.resGroup = resGroup
            self.gameInfo = gameInfo
        }
        
        override func onTempDownloaded(locationPath: String) -> String? {
        	return locationPath
        }
        
        override func onDownloadSuccess(path: String) {
            print("BootGroupDownloadDelegateImpl Success")
            let targetPath = FileUtil.getLocalGroupPath(gameInfo, resGroup: self.resGroup)
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(path, toPath: targetPath, overwrite: true)
                print("download \(self.resGroup.url) Success")

                self.cocosRuntimeGroup.unzip(targetPath, toPath: FileUtil.getGameRootPath(self.gameInfo))
                print("new location:\(targetPath)")
            } catch {
                print("move file error")
            }
        }
        
        override func onDownloadFailed() {
            print("BootGroupDownloadDelegateImpl Failed")
        }
    }
}