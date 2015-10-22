//
//  GameConfig.swift
//  iOSTest
//
//  Created by Rye on 10/21/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

class GameConfig: NSObject {
    var bootGroupMD5: String?
    var bootGroupName: String?
    var bootGroupSize: Int?

    var descript: String?
    
    var designResolutionHeight: Int?
    var designResolutionPolicy: String?
    var designResolutionWidth: Int?

    var entryMD5: String?
    var entryName: String?
    var entrySize: Int?

    var gameName: String?
    var gameType: String?

    var manifestMD5: String?
    var manifestName: String?
    var manifestSize: Int?

    var orientation: String?
    var packageName: String?

    var projectMD5: String?
    var projectName: String?
    var projectSize: Int?

    var runtimeVersion: String?
    var security: String?
    var versionCode: Int?
    var versionName: String?

    override init() {
    	
    }

    static func parseFromFile(path: String) -> GameConfig? {
    	if let json = FileUtil.readJsonFromFile(path) {
    		let gameConfig = GameConfig()
    		gameConfig.bootGroupMD5 = json["boot_group"]["md5"].string
    		gameConfig.bootGroupName = json["boot_group"]["name"].string
    		gameConfig.bootGroupSize = json["boot_group"]["size"].int

    		gameConfig.descript = json["description"].string

    		gameConfig.designResolutionHeight = json["design_resolution"]["height"].int
    		gameConfig.designResolutionPolicy = json["design_resolution"]["policy"].string
    		gameConfig.designResolutionWidth = json["design_resolution"]["width"].int

    		gameConfig.entryMD5 = json["entry_file"]["md5"].string
    		gameConfig.entryName = json["entry_file"]["name"].string
    		gameConfig.entrySize = json["entry_file"]["size"].int

    		gameConfig.gameName = json["game_name"].string
    		gameConfig.gameType = json["game_type"].string

    		gameConfig.manifestMD5 = json["manifest_file"]["md5"].string
    		gameConfig.manifestName = json["manifest_file"]["name"].string
    		gameConfig.manifestSize = json["manifest_file"]["size"].int

    		gameConfig.orientation = json["orientation"].string
    		gameConfig.packageName = json["package_name"].string

    		gameConfig.projectMD5 = json["project_json_file"]["md5"].string
    		gameConfig.projectName = json["project_json_file"]["name"].string
    		gameConfig.projectSize = json["project_json_file"]["size"].int

    		gameConfig.runtimeVersion = json["runtime_version"].string
    		gameConfig.security = json["security"].string
    		gameConfig.versionCode = json["vesion_code"].int
    		gameConfig.versionName = json["version_name"].string
            
            return gameConfig
    	}
        return nil
    }
}