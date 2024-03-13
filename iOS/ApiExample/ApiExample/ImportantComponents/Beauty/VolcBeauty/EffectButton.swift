//
//  EffectButton.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/31.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit

class EffectButton: UIButton {
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.titleLabel?.font = UIFont.systemFont(ofSize: 13)
        self.backgroundColor = UIColor.groupTableViewBackground
        self.setTitleColor(UIColor.systemBlue, for: .normal)
        self.setTitleColor(UIColor.white, for: .selected)
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    var model: EffectModel? {
        didSet {
            guard let model = model else { return }
            self.setTitle(model.name, for: .normal)
        }
    }
    
    override var isSelected: Bool {
        didSet {
            if isSelected {
                self.backgroundColor = UIColor.systemBlue
            } else {
                self.backgroundColor = UIColor.groupTableViewBackground
            }
        }
    }
    
    override func layoutSubviews() {
        super.layoutSubviews()
        self.layer.cornerRadius = self.bounds.size.height * 0.5
        self.layer.masksToBounds = true
    }
}
