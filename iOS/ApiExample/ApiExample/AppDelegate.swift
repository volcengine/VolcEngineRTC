//
//  AppDelegate.swift
//  ApiExample
//
//  Created by bytedance on 2023/9/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import IQKeyboardManagerSwift

@main
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        self.window = UIWindow.init(frame: UIScreen.main.bounds);
        let vc = ViewController.init()
        self.window?.rootViewController = vc
        self.window?.makeKeyAndVisible()

        IQKeyboardManager.shared.enable = true
        
        return true
    }
}

