//
//  ToastView.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/3.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

class ToastView: UIView {

    private var bgView = UIView()

    init(message: String) {
        super.init(frame: .zero)
        
        let minScreen = min(UIScreen.main.bounds.width, UIScreen.main.bounds.height)
        let scale = (minScreen / 375)
        bgView = UIView()
        bgView.backgroundColor = UIColor(white: 0.1, alpha: 0.8)
        bgView.layer.cornerRadius = 4
        bgView.layer.masksToBounds = true
        
        let titleLabel = UILabel()
        titleLabel.numberOfLines = 0
        titleLabel.textColor = .white
        titleLabel.textAlignment = .center
        titleLabel.font = UIFont.systemFont(ofSize: 16.0 * scale, weight: .regular)
        titleLabel.text = message
        
        self.addSubview(bgView)
        bgView.addSubview(titleLabel)

        titleLabel.snp.makeConstraints { make in
            make.center.equalTo(bgView)
            make.width.lessThanOrEqualTo(UIScreen.main.bounds.width - 24 * 2)
        }

        bgView.snp.makeConstraints { make in
            make.left.equalTo(titleLabel).offset(-12)
            make.right.equalTo(titleLabel).offset(12)
            make.top.equalTo(titleLabel).offset(-12)
            make.bottom.equalTo(titleLabel).offset(12)
        }

        self.snp.updateConstraints { make in
            make.size.equalTo(bgView)
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
