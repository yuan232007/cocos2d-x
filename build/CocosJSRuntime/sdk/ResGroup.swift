//
//  ResGroup.swift
//  iOSTest
//
//  Created by Rye on 10/22/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

class ResGroup {
	// todo 添加 patch
	var groupInfoMD5: String?
	var md5: String?
	var name: String?
	var priority: Int?
	var size: Int?
	var url: String?

	init(groupInfoMD5: String?, md5: String?, priority: Int?, size: Int?, url: String?) {
		self.groupInfoMD5 = groupInfoMD5
		self.md5 = md5
		self.priority = priority
		self.size = size
		self.url = url
	}
}