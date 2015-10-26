//
//  FileDownloadAdapter.swift
//  CocosJSRuntime
//
//  Created by Rye on 10/16/15.
//  Copyright © 2015 kinglong huang. All rights reserved.
//

import Foundation

class FileDownloadAdapter: FileDownloadDelegate {
    func onDownloadStart() {}
    func onDownlaodProgress(progress: Double) {}
    func onTempDownloaded(locationPath: String) -> String? { return nil}
    func onDownloadSuccess(path: String) {}
    func onDownloadFailed() {}
    func onDownloadCancel() {}
    func onDownloadRetry() {}
}