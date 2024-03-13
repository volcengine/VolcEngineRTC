//
//  BeautyViewController.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/30.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

class BeautyViewController: BaseViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.addSubview(volBeautyButton)
        view.addSubview(faceUnityBeautyButton)
        
        volBeautyButton.snp.makeConstraints { make in
            make.top.equalTo(topView.snp.bottom).offset(10)
            make.left.equalTo(view).offset(10)
            make.right.equalTo(view.snp.right).offset(-10)
            make.height.equalTo(44)
        }
        
        faceUnityBeautyButton.snp.makeConstraints { make in
            make.top.equalTo(volBeautyButton.snp.bottom).offset(10)
            make.left.equalTo(view).offset(10)
            make.right.equalTo(view.snp.right).offset(-10)
            make.height.equalTo(44)
        }
    }
    
    // MARK: Private method
    @objc func volBeautyButtonClicked()  {
        let viewController = VolcBeautyViewController.init()
        viewController.titleText = "字节美颜"
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    @objc func faceUnityBeautyButtonClicked()  {
        let viewController = FaceUnityViewController.init()
        viewController.titleText = "相芯美颜"
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    // MARK: Lazy laod
    lazy var volBeautyButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("字节美颜", for: .normal)
        button.addTarget(self, action: #selector(volBeautyButtonClicked), for: .touchUpInside)
        return button
    }()
    
    lazy var faceUnityBeautyButton: UIButton = {
        let button = BaseButton.init()
        button.setTitle("相芯美颜", for: .normal)
        button.addTarget(self, action: #selector(faceUnityBeautyButtonClicked), for: .touchUpInside)
        return button
    }()
}
