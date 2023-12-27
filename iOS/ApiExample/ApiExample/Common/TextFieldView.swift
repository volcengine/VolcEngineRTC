//
//  settingItemView.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/11.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit

class TextFieldView: UIView {
    public var title: String = "" {
        willSet {
            self.titleLabel.text = newValue
        }
    }
        
    var text: String? {
        get {
            return self.inputTextField.text
        }
        set {
            self.inputTextField.text = newValue ?? ""
        }
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        self.addSubview(self.titleLabel)
        self.addSubview(self.inputTextField)
        
        self.titleLabel.snp.makeConstraints { make in
            make.top.left.equalToSuperview()
        }
        
        self.inputTextField.snp.makeConstraints { make in
            make.left.equalTo(self.titleLabel.snp.right).offset(10)
            make.right.equalTo(self)
            make.centerY.equalTo(self.titleLabel)
            make.height.equalTo(30)
        }
    }
    
    lazy var titleLabel: UILabel = {
        let label = UILabel.init()
        label.textAlignment = .left
        label.setContentHuggingPriority(.defaultHigh, for: .horizontal)
        return label
    }()
    
    lazy var inputTextField: UITextField = {
        let textField = UITextField()
        textField.borderStyle = .roundedRect
        textField.keyboardType = .numberPad
        return textField
    }()
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
