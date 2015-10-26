//
//  FileDownload.swift
//  iOSTest
//
//  Created by Rye on 10/14/15.
//  Copyright © 2015 Ryeeeeee. All rights reserved.
//

import Foundation

public class FileDownload: NSObject, NSURLSessionDownloadDelegate {
    var requestUrl: NSURL?
    var fileDownloadDelegate: FileDownloadDelegate?
    
    init(urlString: String, delegate fileDownloadDelegate: FileDownloadDelegate) {
        self.requestUrl = NSURL(string: urlString)
        self.fileDownloadDelegate = fileDownloadDelegate
    }
    
    public func startDownload() {
        // FIXED: 应该在主线程回调
        self.fileDownloadDelegate!.onDownloadStart();
        self.getCurrentSession().downloadTaskWithRequest(NSURLRequest(URL: self.requestUrl!)).resume()
    }
    
    func getCurrentSession() -> NSURLSession {
        var predicate: dispatch_once_t = 0
        var currentSession: NSURLSession? = nil
        // 使用 dispatch_once 创建单例
        dispatch_once(&predicate, {
            let config = NSURLSessionConfiguration.defaultSessionConfiguration()
            currentSession = NSURLSession(configuration: config, delegate: self, delegateQueue: nil)
        })
        return currentSession!
    }
    
    /* Sent when a download task that has completed a download.  The delegate should
     * copy or move the file at the given location to a new location as it will be
     * removed when the delegate message returns. URLSession:task:didCompleteWithError: will
     * still be called.
     */
    public func URLSession(session: NSURLSession, downloadTask: NSURLSessionDownloadTask, didFinishDownloadingToURL location: NSURL) {
        //输出下载文件原来的存放目录
        print("location:\(location)")
        let movedPath = self.fileDownloadDelegate!.onTempDownloaded(location.path!)
        
        if let path = movedPath {
            self.fileDownloadDelegate!.onDownloadSuccess(path)
        } else {
            self.fileDownloadDelegate!.onDownloadFailed()
        }
    }
        
    public func URLSession(session: NSURLSession, downloadTask: NSURLSessionDownloadTask, didWriteData bytesWritten: Int64, totalBytesWritten: Int64, totalBytesExpectedToWrite: Int64) {
        // 下载过程中会回调，可以用于监听下载进度
        let written: Double = (Double)(totalBytesWritten)
        let total: Double = (Double)(totalBytesExpectedToWrite)
        let progress: Double = written / total
        print("download on progress \(progress)")
        self.fileDownloadDelegate!.onDownlaodProgress(progress)
    }
        
    /* Sent when a download has been resumed. If a download failed with an
    * error, the -userInfo dictionary of the error will contain an
    * NSURLSessionDownloadTaskResumeData key, whose value is the resume
    * data.
    */
    public func URLSession(session: NSURLSession, downloadTask: NSURLSessionDownloadTask, didResumeAtOffset fileOffset: Int64, expectedTotalBytes: Int64) {
        // 下载偏移，主要用于暂停续传
        print("download pause and resume")
    }
    
    /* 无论是否下载成功都会回调 */
    public func URLSession(session: NSURLSession, task: NSURLSessionTask, didCompleteWithError error: NSError?) {
        if error != nil {
            print("download error")
            self.fileDownloadDelegate!.onDownloadFailed()
        }
    }

}

//enum RequestResult {
//    case Error(NSError)
//    case Value(NSJSONSerialization)
//    init(_ e: NSError?, _ v: NSJSONSerialization) {
//        if let ex = e {
//            self = RequestResult.Error(ex)
//        } else {
//            self = RequestResult.Value(v)
//        }
//    }
//}