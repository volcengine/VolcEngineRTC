//
//  ViewController.swift
//  ApiExample
//
//  Created by bytedance on 2023/9/22.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit
import VolcEngineRTC

class ViewController: UIViewController,UITableViewDelegate,UITableViewDataSource {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.buildUI()
    }

   func buildUI(){
       self.view.backgroundColor = .white
       
       self.view.addSubview(logoImageView)

       logoImageView.snp.makeConstraints { make in
           make.top.equalTo(view.safeAreaLayoutGuide.snp.top).offset(10)
           make.centerX.equalTo(self.view)
       }
       
       self.view.addSubview(backgroundView)

       backgroundView.snp.makeConstraints { make in
           make.top.equalTo(logoImageView.snp.bottom).offset(20)
           make.left.right.equalTo(self.view)
       }
       
       self.view.addSubview(headerLabel)

       headerLabel.snp.makeConstraints { make in
           make.top.equalTo(backgroundView).offset(20)
           make.left.equalTo(self.view).offset(10)
       }
       
       self.view.addSubview(versionLabel)
       versionLabel.snp.makeConstraints { make in
           make.top.equalTo(headerLabel.snp.bottom).offset(10)
           make.left.equalTo(headerLabel)
       }
       
       self.view.addSubview(self.tableview)
       self.tableview.snp.makeConstraints { make in
           make.top.equalTo(versionLabel.snp.bottom)
           make.left.right.bottom.equalTo(self.view)
       }
    }
    
    lazy var dataArray : [[String:[[String:String]]]] = {
        let dic0 = ["快速开始":"QuickStartViewController"];
        let grpup0 = ["基础功能":[dic0]]
        
        let dic1 = ["多房间":"MutiRoomViewController"];
        let grpup1 = ["房间管理":[dic1]]

        let dic2 = ["跨房PK":"CrossRoomPKViewController"]
        let grpup2 = ["音视频传输":[dic2]]
        
        let dic31 = ["原始音频数据":"AudioRawDataViewController"]
        let dic32 = ["音效混音":"AudioEffectMixingViewController"]
        let dic33 = ["音乐混音":"AudioMediaMixingViewController"]
        let dic34 = ["音频特效":"SoundEffectsViewController"]
        let grpup3 = ["音频管理":[dic31,dic32,dic33,dic34]]
        
        let dic42 = ["画中画":"PipViewController"]
        let dic43 = ["常用视频配置":"CommonVideoConfigViewController"]
        let dic44 = ["视频旋转":"VideoRotationViewController"]
        let grpup4 = ["视频管理":[dic42,dic43,dic44]]
        
        let dic51 = ["直推CDN":"PushCDNViewController"]
        let grpup5 = ["直播相关":[dic51]]
        
        let dic62 = ["第三方美颜":"BeautyViewController"]
        let grpup6 = ["重要组件":[dic62]]

        let dataArray = [grpup0,grpup1,grpup2,grpup3,grpup4,grpup5,grpup6]
        
        return dataArray
    }()
    
    lazy var logoImageView: UIImageView = {
        let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFill
        imageView.image = UIImage(named: "volc_logo")
        return imageView
    }()
    
    lazy var backgroundView: UIImageView = {
        let imageView = UIImageView()
        imageView.contentMode = .scaleAspectFill
        imageView.image = UIImage(named: "background")
        return imageView
    }()
    
    lazy var headerLabel: UILabel = {
        let headerLabel = UILabel()
        headerLabel.text = "VERTC API Example"
        headerLabel.font = UIFont.boldSystemFont(ofSize: 20)
        headerLabel.textColor = UIColor.black
        headerLabel.sizeToFit()
        return headerLabel
    }()

    lazy var versionLabel: UILabel = {
        let versionLabel = UILabel()
        versionLabel.text = "SDK版本 v" + ByteRTCVideo.getSDKVersion()
        versionLabel.font = UIFont.systemFont(ofSize: 16)
        versionLabel.textColor = UIColor.black
        versionLabel.sizeToFit()
        return versionLabel
    }()
    
    lazy var tableview : UITableView = {
        let tableView = UITableView.init(frame: self.view.bounds, style: .grouped)
        tableView.delegate = self
        tableView.dataSource = self
        tableView.register(UITableViewCell.self, forCellReuseIdentifier: "viewControllerCell")
        
        tableView.backgroundColor = .clear
        
        return tableView
    }()
    

    // MARK: delegate
    func numberOfSections(in tableView: UITableView) -> Int {
        return self.dataArray.count
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let dic = dataArray[section]
        let values = dic.values.first
        return values?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let dic:[String:[[String:String]]] = self.dataArray[section]
        let title = dic.keys.first
        return title
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "viewControllerCell", for: indexPath)
        let dic:[String:[[String:String]]] = self.dataArray[indexPath.section]
    
        let array:[[String:String]] = dic.values.first!
        
        let cellInfo = Array(array)[indexPath.row]
        
        cell.textLabel?.text = cellInfo.keys.first

        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let dic:[String:[[String:String]]] = self.dataArray[indexPath.section]
    
        let array:[[String:String]] = dic.values.first!
        
        let cellInfo = Array(array)[indexPath.row]
        
        let className = cellInfo.values.first! as String
                
        if NSClassFromString("ApiExample." + className) is UIViewController.Type {
            let classType = NSClassFromString("ApiExample." + className) as! BaseViewController.Type
   
            let viewController = classType.init()
            viewController.titleText = cellInfo.keys.first!
            let nav:UINavigationController = UINavigationController.init(rootViewController: viewController)
            nav.modalPresentationStyle = .fullScreen
            self.present(nav, animated: true)
        }
    }
}
