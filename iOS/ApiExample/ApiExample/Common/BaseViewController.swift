//
//  BaseViewController.swift
//  ApiExample
//
//  Created by bytedance on 2023/9/28.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit

class BaseViewController : UIViewController {
    var titleText :String = "" {
        didSet {
            self.titleLabel.text = titleText;
        }
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    deinit {
        print("class: \(type(of: self)) func: \(#function)")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.view.backgroundColor = .white
        self.navigationController?.navigationBar.isHidden = true
        
        self.view.addSubview(self.topView)
        self.topView.snp.makeConstraints { make in
            make.top.left.right.equalTo(self.view)
            
            let topSafeArea = UIApplication.shared.keyWindow?.safeAreaInsets.top ?? 0.0
            make.height.equalTo(44 + topSafeArea)
        }
        
        self.topView.addSubview(self.backButton)
        self.backButton.snp.makeConstraints { make in
            make.left.equalTo(10)
            make.bottom.equalTo(self.topView).offset(-10)
        }
        
        self.topView.addSubview(self.titleLabel)
        self.titleLabel.snp.makeConstraints { make in
            make.centerX.equalTo(self.topView)
            make.centerY.equalTo(self.backButton)
        }
    }
    
    // MARK: Private method
    // 返回
    @objc func buttonTapped() {
        if ((self.navigationController?.viewControllers.count)! > 1) {
            self.navigationController!.popViewController(animated: true)
        } else {
            self.dismiss(animated: true)
        }
    }
    
    // MARK: Lazy laod
    public lazy var topView : UIView = {
        let topView:UIView = UIView.init()
        topView.backgroundColor = .groupTableViewBackground
        return topView
    }()
    
    lazy var backButton: UIButton = {
        let button = UIButton(type: .custom)
        button.setTitle("返回", for: .normal)
        button.setTitleColor(.black, for: .normal)
        button.setImage(UIImage(named: "back_button"), for: .normal)
        button.addTarget(self, action: #selector(buttonTapped), for: .touchUpInside)
        return button
    }()
    
    private lazy var titleLabel: UILabel = {
        let titleLabel = UILabel()
        titleLabel.textAlignment = .center
        titleLabel.font = UIFont.systemFont(ofSize: 18)
        return titleLabel
    }()
}
