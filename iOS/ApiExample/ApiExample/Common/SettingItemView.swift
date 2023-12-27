//
//  settingItemView.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/11.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit

class SettingItemView: UIView {
    public var title: String = "" {
        willSet {
            self.titleLabel.text = newValue
        }
    }
        
    var text: String? {
        return self.inputTextField.text
    }

    public var onValueChanged: ((String) -> Void)?
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        self.addSubview(self.titleLabel)
        self.addSubview(self.inputTextField)
        self.addSubview(self.button)
        
        self.titleLabel.snp.makeConstraints { make in
            make.top.left.bottom.equalToSuperview()
        }
        
        self.inputTextField.snp.makeConstraints { make in
            make.left.equalTo(self.titleLabel.snp.right).offset(10)
            make.centerY.equalTo(self.titleLabel)
            make.width.equalTo(60)
            make.height.equalTo(30)
        }
        
        self.button.snp.makeConstraints { make in
            make.left.equalTo(self.inputTextField.snp.right).offset(10)
            make.centerY.equalTo(self.inputTextField)
            make.right.equalToSuperview()
        }
    }
    
    @objc func onButtonCLicked()  {
        let text = self.inputTextField.text
        onValueChanged?(text ?? "")
    }
    
    lazy var titleLabel: UILabel = {
        let label = UILabel.init()
        label.textAlignment = .center
        return label
    }()
    
    lazy var inputTextField: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        textField.keyboardType = .numberPad
        return textField
    }()
    
    lazy var button: UIButton = {
        let button = UIButton(type: .system)
        button.setTitle("确定", for: .normal)
        button.addTarget(self, action: #selector(onButtonCLicked), for: .touchUpInside)
        return button
    }()
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
