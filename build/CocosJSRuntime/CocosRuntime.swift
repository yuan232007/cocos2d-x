//
//  CocosRuntime.swift
//  CocosJSRuntime
//
//  Created by Rye on 10/16/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

import Foundation

/**
 * 提供给 oc 的类必须继承自 NSOject 或其子类
 */
public class CocosRuntime: NSObject {
	static var sharedInstance: CocosRuntime = CocosRuntime()
    var gameInfo: GameInfo?
    
    func startPreRunGame(gameInfo: GameInfo) {
        PreRunGame.sharedInstance.start(gameInfo)
    }
}