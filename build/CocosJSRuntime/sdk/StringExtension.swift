//
//  StringExtension.swift
//  iOSTest
//
//  Created by Rye on 10/19/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation
extension String {
    
    func indexOf(target: String) -> Int? {
        if let range = self.rangeOfString(target) {
            return startIndex.distanceTo(range.startIndex)
        } else {
            return nil
        }
    }
    
    func lastIndexOf(target: String) -> Int? {
        if let range = self.rangeOfString(target, options: .BackwardsSearch) {
            return startIndex.distanceTo(range.startIndex)
        } else {
            return nil
        }
    }
    
    func substringToIndex(index: Int?) -> String? {
        if let lastIndex = index {
            return substringToIndex(startIndex.advancedBy(lastIndex))
        } else {
            return nil
        }
    }
    
    func substringFromIndex(index: Int?) -> String? {
        if let lastIndex = index {
            return substringFromIndex(startIndex.advancedBy(lastIndex))
        } else {
            return nil
        }
    }
    
}