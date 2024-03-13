//
//  SettingSwitchItem.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/17.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

class SwitchSettingView: UIView {

    private let label: UILabel = {
        let label = UILabel()
        label.textAlignment = .left

        return label
    }()

    private let switchControl: UISwitch = {
        let switchControl = UISwitch()
        
        return switchControl
    }()
    
    var switchValueChanged: ((Bool) -> Void)?

    init(text: String) {
        super.init(frame: .zero)
        setupView()
        setupConstraints()
        
        switchControl.addTarget(self, action: #selector(switchValueChanged(_:)), for: .valueChanged)
        label.text = text
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private func setupView() {
        addSubview(label)
        addSubview(switchControl)
    }

    private func setupConstraints() {
        label.snp.makeConstraints { make in
            make.top.bottom.equalToSuperview()
            make.left.equalToSuperview()
        }
        
        switchControl.snp.makeConstraints { make in
            make.top.bottom.equalToSuperview()
            make.left.equalTo(label.snp.right).offset(16)
            make.right.equalToSuperview()
        }
    }
    
    @objc private func switchValueChanged(_ sender: UISwitch) {
        switchValueChanged?(sender.isOn)
    }
}
