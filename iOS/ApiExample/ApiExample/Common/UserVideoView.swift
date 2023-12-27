//
//  UserVideoView.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/7.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit

class UserVideoView: UIView {
    public var userId: String = "" {
        willSet {
            if newValue.count != 0 {
                self.userIdLabel.text = "\(newValue) "
            } else {
                self.userIdLabel.text = ""
            }
        }
    }
    
    public lazy var videoView: UIView = {
        let view = UIView.init()
        return view
    }()
    
    lazy var userIdLabel: UILabel = {
        let label = UILabel.init()
        label.textAlignment = .center
        label.backgroundColor = .white
        label.layer.cornerRadius = 4
        label.layer.masksToBounds = true
        return label
    }()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.addSubview(self.videoView)
        self.addSubview(self.userIdLabel)
        
        self.videoView.snp.makeConstraints { make in
            make.left.top.right.equalTo(self)
            make.bottom.equalTo(self)
        }
        
        self.userIdLabel.snp.makeConstraints { make in
            make.left.equalTo(self).offset(5)
            make.bottom.equalTo(self).offset(-5)
            make.height.equalTo(24)
        }
    }
    
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
