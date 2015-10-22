//
//  FileDownloadDelegate.swift
//  iOSTest
//
//  Created by Rye on 10/15/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

protocol FileDownloadDelegate {
    func onDownloadStart()
    func onDownlaodProgress(progress: Double)
    func onTempDownloaded(locationPath: String) -> String?
    func onDownloadSuccess(path: String)
    func onDownloadFailed()
    func onDownloadCancel()
    func onDownloadRetry()
}
