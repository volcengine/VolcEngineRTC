//
//  AppDelegate.swift
//  ApiExample
//
//  Created by bytedance on 2023/9/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import IQKeyboardManagerSwift
import TTSDKFramework

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        self.window = UIWindow.init(frame: UIScreen.main.bounds);
        let vc = ViewController.init()
        self.window?.rootViewController = vc
        self.window?.makeKeyAndVisible()

        IQKeyboardManager.shared.enable = true
        
        // 初始化TTSDK
        self.setupTTSDK()
        
        return true
    }
    
    func setupTTSDK() {
        // 用拿到的APPID创建TTSDKConfiguration
        let configuration = TTSDKConfiguration.defaultConfiguration(withAppID: TTSDKAppID)
        // 添加控制台的 App 信息
        configuration.appName = TTSDKAppName
        configuration.channel = "local_test"
        configuration.bundleID = TTSDKBundleID
        let licenseFilePath = Bundle.main.path(forResource: "tt_license.lic", ofType: nil)
        configuration.licenseFilePath = licenseFilePath ?? ""
        TTSDKManager.start(with: configuration)
        TVLManager.startOpenGLESActivity()

    }
}

