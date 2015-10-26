//
//  PreRunGame.swift
//  CocosJSRuntime
//
//  Created by Rye on 10/16/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

import Foundation

class PreRunGame {
    // the right way to write a singleton in swift
    static let sharedInstance = PreRunGame()
    
    var gameInfo: GameInfo? = nil
    var remoteConfigPath: String? = nil
    var localConfigPath: String? = nil
    var gameManifest: GameManifest? = nil
    var fileDownload: FileDownload? = nil

    var gameConfig: GameConfig? = nil

    private init() {
    
    }
    
    func start(gameInfo: GameInfo) {
        print("start")
        self.gameInfo = gameInfo
        self.remoteConfigPath = FileUtil.getRemoteConfigPath(gameInfo)
        self.localConfigPath = FileUtil.getLocalConfigPath(gameInfo)
        self.downloadRemoteConfigFile()
    }
    
    func reset() {}
    
    /**
     * 下载 config.json 
     */
    private func downloadRemoteConfigFile() {
        print("downloadRemoteConfigFile")
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
            self.fileDownload = FileDownload(urlString: self.gameInfo!.downloadUrl + FileUtil.ConfigFileName, delegate: ConfigDownloadDelegateImpl(preRunGame: self))
            self.fileDownload!.startDownload()
        }
    }
    
    /**
     * 更新本地 config.json
     */
    private func updateLocalConfigFile(path: String) {
        print("updateLocalConfigFile")
        do {
            try FileUtil.moveFile(path, toPath: FileUtil.getLocalConfigPath(self.gameInfo!), overwrite: true)
            PreRunGame.sharedInstance.checkLocalManifestFile()
        } catch {
            print("updateLocalConfigFile Error")
        }
    }
    
    /**
     * 检查本地 manifest.json
     */
    private func checkLocalManifestFile() {
        print("checkLocalManifestFile")
        if FileUtil.fileExists(FileUtil.getLocalManifestPath(self.gameInfo!, gameConfig: self.gameConfig!)) && isLocalManifestMD5Correct() {
                checkEntryFile();
        } else {
            downloadRemoteManifestFile()
        }
    }
    
    /**
     * 下载 manifest.json
     */
    private func downloadRemoteManifestFile() {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
            self.fileDownload = FileDownload(urlString: self.gameInfo!.downloadUrl + self.gameConfig!.manifestName!, delegate: ManifestDownloadDelegateImpl(preRunGame: self))
            self.fileDownload!.startDownload()
        }
    }
    
    /**
     * 解析游戏配置文件
     */
    private func parseGameConfigFile(path: String) {
        gameConfig = GameConfig.parseFromFile(path)
    }
    
    /**
     * 检查 main.jsc
     */
    private func checkEntryFile() {
        print("checkEntryFile")
        if FileUtil.fileExists(FileUtil.getLocalEntryPath(self.gameInfo!, gameConfig: self.gameConfig!)) && isLocalEntryMD5Correct() {
            checkProjectJsonFile()
        } else {
            downloadEntryFile()
        }
    }
    
    /**
     * 下载 main.jsc
     */
    private func downloadEntryFile() {
        print("downloadEntryFile")
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
            self.fileDownload = FileDownload(urlString: self.gameInfo!.downloadUrl + self.gameConfig!.entryName!, delegate: EntryDownloadDelegateImpl(preRunGame: self))
            self.fileDownload!.startDownload()
        }
    }
    
    /**
     * 检查 project-runtime.json
     */
    private func checkProjectJsonFile() {
        print("checkProjectJsonFile")
        if FileUtil.fileExists(FileUtil.getLocalProjectPath(self.gameInfo!, gameConfig: self.gameConfig!)) && isLocalProjectMD5Correct() {
            checkBootGroup()
        } else {
            downloadProjectJsonFile()
        }
    }
    
    /**
     * 下载 project-runtime.json
     */
    private func downloadProjectJsonFile() {
        print("downloadProjectJsonFile")
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
            self.fileDownload = FileDownload(urlString: self.gameInfo!.downloadUrl + self.gameConfig!.projectName!, delegate: ProjectDownloadDelegateImpl(preRunGame: self))
            self.fileDownload!.startDownload()
        }
    }
    
    /**
     * 删除不相关的组
     */
    private func deleteNoRefGroups() {
        print("deleteNoRefGroups")
        
    }
    
    /**
     * 检查首场景资源
     */
    private func checkBootGroup() {
        print("checkBootGroup")
        if FileUtil.fileExists(FileUtil.getLocalBootGroupPath(self.gameInfo!, gameConfig: self.gameConfig!)) && isLocalBootGroupMD5Correct() {
            checkEntryFile();
        } else {
            downloadBootGroup()
        }
    }

    /**
     * 下载首场景资源
     */
    private func downloadBootGroup() {
        print("downloadBootGroup")
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)) {
            self.fileDownload = FileDownload(urlString: self.gameInfo!.downloadUrl + "group/" + self.gameConfig!.bootGroupName!, delegate: BootGroupDownloadDelegateImpl(preRunGame: self, gameInfo: self.gameInfo!, gameConfig: self.gameConfig!))
            self.fileDownload!.startDownload()
        }
    }
    
    /**
     * 开始游戏
     */
    private func startGame() {
        print("StartGame")
    }
    
    /**
     * 检查本地 config.json 的 md5 值是否正确
     */
    private func isLocalConfigMD5Correct() -> Bool {
        let localConfigMD5 = FileUtil.getFileMD5(FileUtil.getLocalConfigPath(self.gameInfo!))
        let remoteConfigMD5 = FileUtil.getFileMD5(FileUtil.getRemoteConfigPath(self.gameInfo!))
        if let localMD5 = localConfigMD5, remoteMD5 = remoteConfigMD5 where localMD5 == remoteMD5 {
            return true
        }
        return false
    }
        
    private func isLocalBootGroupMD5Correct() -> Bool {
        let localBootMD5 = FileUtil.getFileMD5(FileUtil.getLocalBootGroupPath(self.gameInfo!, gameConfig: gameConfig!))
        if let localMD5 = localBootMD5, remoteMD5 = gameConfig!.bootGroupMD5 where localMD5 == remoteMD5 {
            return true
        }
        return false
    }

    /**
     * 检查本地 manifest.json 的 md5 值是否正确
     */
    private func isLocalManifestMD5Correct() -> Bool {
        let localManifestMD5 = FileUtil.getFileMD5(FileUtil.getLocalManifestPath(self.gameInfo!, gameConfig: self.gameConfig!))
        if let localMD5 = localManifestMD5, remoteMD5 = gameConfig!.manifestMD5 where localMD5 == remoteMD5 {
            return true
        }
        return false
    }
    
    /**
     * 检查本地 project-runtime.json 的 md5 值是否正确
     */
    private func isLocalProjectMD5Correct() -> Bool {
        let localProjectMD5 = FileUtil.getFileMD5(FileUtil.getLocalProjectPath(self.gameInfo!, gameConfig: self.gameConfig!))
        if let localMD5 = localProjectMD5, remoteMD5 = gameConfig!.projectMD5 where localMD5 == remoteMD5 {
            return true
        }
        return false 
    }
   
    /**
     * 检查本地 main.jsc 的 md5 值是否正确
     */
    private func isLocalEntryMD5Correct() -> Bool {
        let localEntryMD5 = FileUtil.getFileMD5(FileUtil.getLocalEntryPath(self.gameInfo!, gameConfig: self.gameConfig!))
        if let localMD5 = localEntryMD5, remoteMD5 = gameConfig!.entryMD5 where localMD5 == remoteMD5 {
            return true
        }
        return false
    }
    
    /* 
     * 下载 config.json
     */
    class ConfigDownloadDelegateImpl: FileDownloadAdapter {
        let preRunGame: PreRunGame
        
        init(preRunGame: PreRunGame) {
            self.preRunGame = preRunGame
        }
        
        override func onTempDownloaded(locationPath: String) -> String? {
            let targetPath = FileUtil.getRemoteConfigPath(self.preRunGame.gameInfo!)
            
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(locationPath, toPath: targetPath, overwrite: true)
                PreRunGame.sharedInstance.parseGameConfigFile(targetPath)

                print("new location:\(targetPath) :")
                return targetPath

            } catch {
                print("move file error")
            }
            return nil
        }
        
        override func onDownloadSuccess(path: String) {
            print("ConfigDownloadDelegateImpl Success")
            PreRunGame.sharedInstance.updateLocalConfigFile(path)
        }
        
        override func onDownloadFailed() {
            print("ConfigDownloadDelegateImpl Failed")
        }

    }
    
    /* 下载 mainifest.json */
    class ManifestDownloadDelegateImpl: FileDownloadAdapter {
        let preRunGame: PreRunGame
        
        init(preRunGame: PreRunGame) {
            self.preRunGame = preRunGame
        }
        
        override func onTempDownloaded(locationPath: String) -> String? {
            let targetPath = FileUtil.getLocalManifestPath(self.preRunGame.gameInfo!, gameConfig: self.preRunGame.gameConfig!)
            
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(locationPath, toPath: targetPath, overwrite: true)
                print("new location:\(targetPath)")
                return targetPath

            } catch {
                print("move file error")
            }
            return nil
        }
        
        override func onDownloadSuccess(path: String) {
            print("ManifestDownloadDelegateImpl Success")
            self.preRunGame.gameManifest = GameManifest.readFromFile(path)
            CocosRuntimeGroup.sharedInstance.initialize(self.preRunGame.gameInfo!, gameConfig: self.preRunGame.gameConfig!, gameManifest: self.preRunGame.gameManifest!)
            PreRunGame.sharedInstance.checkEntryFile()
        }
        
        override func onDownloadFailed() {
            print("ManifestDownloadDelegateImpl Failed")
        }
    }

    /* 下载 main.jsc */
    class EntryDownloadDelegateImpl: FileDownloadAdapter {
        let preRunGame: PreRunGame
        
        init(preRunGame: PreRunGame) {
            self.preRunGame = preRunGame
        }
        
        override func onTempDownloaded(locationPath: String) -> String? {
            let targetPath = FileUtil.getLocalEntryPath(self.preRunGame.gameInfo!, gameConfig: self.preRunGame.gameConfig!)
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(locationPath, toPath: targetPath, overwrite: true)
                print("new location:\(targetPath)")
                return targetPath
            } catch {
                print("move file error")
            }
            return nil
        }
        
        override func onDownloadSuccess(path: String) {
            print("EntryDownloadDelegateImpl Success")
            PreRunGame.sharedInstance.checkProjectJsonFile()
        }
        
        override func onDownloadFailed() {
            print("EntryDownloadDelegateImpl Failed")
        }
    }

    /* 下载 project-runtime.json */
    class ProjectDownloadDelegateImpl: FileDownloadAdapter {
        let preRunGame: PreRunGame
        
        init(preRunGame: PreRunGame) {
            self.preRunGame = preRunGame
        }
        
        override func onTempDownloaded(locationPath: String) -> String?{
            let targetPath = FileUtil.getLocalProjectPath(self.preRunGame.gameInfo!, gameConfig: self.preRunGame.gameConfig!)
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(locationPath, toPath: targetPath, overwrite: true)
                return targetPath
                print("new location:\(targetPath)")
            } catch {
                print("move file error")
            }
            return nil
        }
        
        override func onDownloadSuccess(path: String) {
            print("ProjestDownloadDelegateImpl Success")
            PreRunGame.sharedInstance.checkBootGroup()
        }
        
        override func onDownloadFailed() {
            print("ProjestDownloadDelegateImpl/ Failed")
        }
    }

    /* 下载 boot.cpk */
    class BootGroupDownloadDelegateImpl: FileDownloadAdapter {
        let preRunGame: PreRunGame
        let gameConfig: GameConfig
        let gameInfo: GameInfo
        
        init(preRunGame: PreRunGame, gameInfo: GameInfo, gameConfig: GameConfig) {
            self.preRunGame = preRunGame
            self.gameInfo = gameInfo
            self.gameConfig = gameConfig
        }
        
        override func onTempDownloaded(locationPath: String) -> String? {
            return locationPath
        }
        
        override func onDownloadSuccess(path: String) {
            print("BootGroupDownloadDelegateImpl Success")
            let targetPath = FileUtil.getLocalBootGroupPath(self.gameInfo, gameConfig: self.gameConfig)
            do {
                try FileUtil.ensureDirectory(FileUtil.getParentDirectory(targetPath)!)
                try FileUtil.moveFile(path, toPath: targetPath, overwrite: true)
                print("tmp download \(path)")
                print("download \(targetPath) Success")
                let gameRootPath = FileUtil.getGameRootPath(self.gameInfo)
                if ZipHelper.unzipFileAtPath(targetPath, toDestination: gameRootPath) {
                    print("unzip success \(gameRootPath)")
                } else {
                    print("unzip failed \(gameRootPath)")
                }
                PreRunGame.sharedInstance.startGame()
            } catch {
                print("move file error")
            }
        }
        
        override func onDownloadFailed() {
            print("BootGroupDownloadDelegateImpl Failed")
        }
    }

}