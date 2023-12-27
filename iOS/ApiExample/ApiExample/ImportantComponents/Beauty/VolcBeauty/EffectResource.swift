//
//  EffectResource.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/2.
//  Copyright © 2021 bytedance. All rights reserved.
//

import Foundation

class EffectResource {
    
    static func licensePath() -> String {
        let bundlePath = Bundle.main.path(forResource: "LicenseBag", ofType: "bundle") ?? ""
        let licensePath = "\(bundlePath)/\(CVLicenseName)"
        checkPathExist(path: licensePath)
        
        return licensePath
    }
    
    static func modelPath() -> String {
        let modelPath = Bundle.main.path(forResource: "ModelResource", ofType: "bundle") ?? ""
        checkPathExist(path: modelPath)
        
        return modelPath
    }
    
    static func getByteEffectPortraitPath() -> String {
        let portraitPrefix = Bundle.main.path(forResource: "StickerResource", ofType: "bundle") ?? ""
        let name = "matting_bg"
        let path = "\(portraitPrefix)/stickers/\(name)"
        checkPathExist(path: path)
        
        return path
    }
    
    static func beautyCameraPath() -> String {
        let bundlePath = Bundle.main.path(forResource: "ComposeMakeup", ofType: "bundle") ?? ""
        let beautyCameraPath = "\(bundlePath)/ComposeMakeup/beauty_IOS_lite"
        checkPathExist(path: beautyCameraPath)
        
        return beautyCameraPath
    }
    
    static func reshapeCameraPath() -> String {
        let bundlePath = Bundle.main.path(forResource: "ComposeMakeup", ofType: "bundle") ?? ""
        let reshapeCameraPath = "\(bundlePath)/ComposeMakeup/reshape_lite"
        checkPathExist(path: reshapeCameraPath)
        
        return reshapeCameraPath
    }
    
    static func stickerPath(withName stickerName: String) -> String {
        let bundlePath = Bundle.main.path(forResource: "StickerResource", ofType: "bundle") ?? ""
        let stickerPath = "\(bundlePath)/stickers/\(stickerName)"
        checkPathExist(path: stickerPath)
        
        return stickerPath
    }
    
    static func filterPath(withName filterName: String) -> String {
        let bundlePath = Bundle.main.path(forResource: "FilterResource", ofType: "bundle") ?? ""
        let filterPath = "\(bundlePath)/Filter/\(filterName)"
        checkPathExist(path: filterPath)
        
        return filterPath
    }
    
    static func checkPathExist(path: String) {
        let exist = FileManager.default.fileExists(atPath: path)
        
        if !exist {
            NSLog("EffectResource path does not exist: \n\(path)")
            ToastComponents.shared.show(withMessage: "资源不存在:\(path)")
        }
    }
}
