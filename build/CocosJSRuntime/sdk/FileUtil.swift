//
//  FileUtil.swift
//  CocosJSRuntime
//
//  Created by Rye on 10/16/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

import Foundation

class FileUtil {
    static let remoteConfigFileNamePrefix = "config.json.remote"
    static let ConfigFileName = "config.json"
    // static let ManifestFileName = "manifest.json"
    // static let EntryFileName = "main.jsc"
    // static let ProjectFileName = "project-runtime.json"
    // static let BootGroupFileName = "boot.cpk"
    
    static let fileManager = NSFileManager.defaultManager()
    // todo magic number

    /**
     * 获取 CocosRuntime 文件存取根目录
     * Library/CocosRuntime
     */
    static func getCocosRuntimeRootPath () -> String {
        return ChannelConfig.cocosRuntimeRootPath
    }
    
    /**
     * 获取游戏存储根目录
     * Library/CocosRuntime/Games
     */
    static func getGamesDir() -> String {
        return getCocosRuntimeRootPath() + "/Games"
    }
    
    /**
     * 获取服务端下载的 config.json 的存储路径
     * Library/CocosRuntime/Games/config.json.remote.$GameKey
     */
    static func getRemoteConfigPath(gameInfo: GameInfo) -> String {
        return getGamesDir() + "/" + remoteConfigFileNamePrefix + "." + gameInfo.gameKey
    }
    
    /**
     * 获取游戏根目录
     * Library/CocosRuntime/Games/$GameKey
     */
    static func getGameRootPath(gameInfo: GameInfo) -> String {
        return getGamesDir() + "/" + gameInfo.gameKey
    }
    
    /**
     * 获得游戏的 config.json 文件
     * Library/CocosRuntime/Games/$GameKey/config.json
     */
    static func getLocalConfigPath(gameInfo: GameInfo) -> String {
        return getGameRootPath(gameInfo) + "/" + ConfigFileName
    }
    
    /**
     * 获得游戏的 manifest.json 文件
     * Library/CocosRuntime/Games/$GameKey/manifest.json
     */
    static func getLocalManifestPath(gameInfo: GameInfo, gameConfig: GameConfig) -> String {
        return getGameRootPath(gameInfo) + "/" + gameConfig.manifestName!
    }
    
    /**
     * 获得游戏的 project-runtime.json 文件
     * Library/CocosRuntime/Games/$GameKey/project-runtime.json
     */
    static func getLocalProjectPath(gameInfo: GameInfo, gameConfig: GameConfig) -> String {
        return getGameRootPath(gameInfo) + "/" + gameConfig.projectName!
    }
    
    /**
     * 获得游戏的 main.jsc 文件
     * Library/CocosRuntime/Games/$GameKey/main.jsc
     */
    static func getLocalEntryPath(gameInfo: GameInfo, gameConfig: GameConfig) -> String {
        return getGameRootPath(gameInfo) + "/" + gameConfig.entryName!
    }
    
    /**
     * 获取游戏组存储根路径
     */
    static func getLocalGameGroupRootPath(gameInfo: GameInfo) -> String {
        return getGameRootPath(gameInfo) + "/" + "group"
    }
   
    /**
     * 根据 ResGroup 和 GameInfo 获取本地 Group 的存放路径
     */
    static func getLocalGroupPath(gameInfo: GameInfo, resGroup: ResGroup) -> String {
        return getGameRootPath(gameInfo) + "/" + resGroup.url!
    }

    /**
     * 获得游戏的 boot.cpk 文件
     * Library/CocosRuntime/Games/$GameKey/boot.cpk
     */
    static func getLocalBootGroupPath(gameInfo: GameInfo, gameConfig: GameConfig) -> String {
        return getLocalGameGroupRootPath(gameInfo) + "/" + gameConfig.bootGroupName!
    }
    
    /**
     * 确保目录存在, 会补全中间缺少的目录，如果创建出错则抛出异常
     */
    static func ensureDirectory(path: String) throws {
        try fileManager.createDirectoryAtPath(path, withIntermediateDirectories: true, attributes: nil)
    }
    
    /**
     * 获取父目录
     */
    static func getParentDirectory(path: String) -> String? {
        return path.substringToIndex(path.lastIndexOf("/"))
    }
    
    /**
     * 获取文件名
     */
    static func getBaseName(path: String) -> String? {
        return path.substringFromIndex(path.lastIndexOf("/"))
    }
    
    /**
     * 移动文件
     */
    static func moveFile(fromPath: String, toPath: String, overwrite: Bool=false) throws {
        try FileUtil.ensureDirectory(FileUtil.getParentDirectory(toPath)!)
        if overwrite && fileManager.fileExistsAtPath(toPath) {
            try fileManager.removeItemAtPath(toPath)
        }
        try fileManager.moveItemAtPath(fromPath, toPath: toPath)
    }
    
    /*
     * 判断文件是否存在
     */
    static func fileExists(path: String) -> Bool {
        return fileManager.fileExistsAtPath(path)
    }
       
    /*
     * 从文件读取 JSON 数据
     */
    static func readJsonFromFile(path: String) -> JSON? {
        let data = NSData(contentsOfFile: path)
        let content = NSString(data: data!, encoding: NSUTF8StringEncoding)
        print("readJsonFromFile path: \(path) :\(content)" )
        let json = JSON(data: content!.dataUsingEncoding(NSUTF8StringEncoding, allowLossyConversion: false)!)
        return json
    }

    /**
     * 将 JSON 数据写入到文件中
     */
    static func writeJsonToFile(json: JSON) {

    }

    /**
     * 获得文件的 md5 值
     */
    static func getFileMD5(path: String) -> String? {
        if let data = NSData(contentsOfFile: path) {
            return data.md5()
        } else {
            return nil
        }
    }
}