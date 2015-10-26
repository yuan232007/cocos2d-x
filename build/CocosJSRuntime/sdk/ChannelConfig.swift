//
//  ChannelConfig.swift
//  iOSTest
//
//  Created by Rye on 10/21/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

public class ChannelConfig: NSObject {
    //
    public static var channel: String?
	// todo magic number
	public static var cocosRuntimeRootPath = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.LibraryDirectory, NSSearchPathDomainMask.UserDomainMask, true)[0] + "/CocosRuntime"
	
}
