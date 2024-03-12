//
//  Config.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/2.
//  Copyright © 2021 bytedance. All rights reserved.
//


let kAppID  = ""
let kAppKey = ""

let kCDNUrl = ""

let kPullUrl = ""

let CVLicenseNameDebug = ""
let CVLicenseNameRelease = ""

#if DEBUG
let CVLicenseName = CVLicenseNameDebug
#else
let CVLicenseName = CVLicenseNameRelease
#endif

let TTSDKAppID = ""
let TTSDKAppName = ""
let TTSDKBundleID = ""
