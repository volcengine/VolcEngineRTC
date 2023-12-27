//
//  Tool.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

import Foundation

// 用户名&房间名正则
let inputRegex = "^[a-zA-Z0-9@._-]{1,128}$"

// 获取token,建议从服务端获取
func generatorToken(roomId:String,userId:String) -> String {
    return TokenGenerator.token(withAppID: kAppID, appKey: kAppKey, roomId: roomId, uid: userId)
}

// 检查用户名或者房间名是否合法
func checkValid(_ string: String) -> Bool {
    do {
        let regex = try NSRegularExpression(pattern: inputRegex, options: [])
        let results = regex.matches(in: string, options: [], range: NSRange(location: 0, length: string.utf16.count))
        return results.count > 0
    } catch {
        print("Invalid regex: \(error.localizedDescription)")
        return false
    }
}

// 获取safaArea
func getSafeAreaInsets() -> UIEdgeInsets {
    if #available(iOS 11.0, *) {
        return UIApplication.shared.keyWindow?.safeAreaInsets ?? UIEdgeInsets.zero
    } else {
        return UIEdgeInsets.zero
    }
}
