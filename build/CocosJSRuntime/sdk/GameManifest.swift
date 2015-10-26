//
//  GameManifest.swift
//  iOSTest
//
//  Created by Rye on 10/22/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

class GameManifest {
	var resourceGroupJSON: JSON?

	static func readFromFile(path: String) -> GameManifest? {
		if let json = FileUtil.readJsonFromFile(path) {
    		var gameManifest = GameManifest()
    		gameManifest.resourceGroupJSON = json["res_groups"]
    	}
        return nil
	}
}