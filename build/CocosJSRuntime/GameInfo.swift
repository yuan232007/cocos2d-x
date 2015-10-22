//
//  GameInfo.swift
//  CocosJSRuntime
//
//  Created by Rye on 10/16/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

import Foundation

public class GameInfo: NSObject {

    var gameKey: String
    var downloadUrl: String
    var gameName: String
    var gameVersionName: String
    var gameVersionCode: Int

    public init(gameKey: String, downloadUrl: String, gameName: String, gameVersionName: String, gameVersionCode: Int) {
        self.gameKey = gameKey
        self.downloadUrl = downloadUrl
        self.gameName = gameName
        self.gameVersionName = gameVersionName
        self.gameVersionCode = gameVersionCode
    }
}