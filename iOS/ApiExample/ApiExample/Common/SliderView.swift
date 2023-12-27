//
//  SliderView.swift
//  ApiExample
//
//  Created by bytedance on 2023/12/11.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

class SliderView: UIView {

    var label: UILabel
    var slider: UISlider
    var valueLabel: UILabel
    var onValueChanged: ((Int32) -> Void)?

    var title: String {
        get {
            return self.label.text ?? ""
        }
        set {
            self.label.text = newValue
        }
    }
    
    init(minValue: Float, maxValue: Float, defaultValue: Float) {

        self.label = UILabel()
        self.slider = UISlider()
        self.valueLabel = UILabel()
        self.valueLabel.textAlignment = .right

        super.init(frame: .zero)

        self.slider.minimumValue = minValue
        self.slider.maximumValue = maxValue
        self.slider.value = defaultValue
        self.valueLabel.text = String(Int32(defaultValue))

        addSubview(label)
        addSubview(slider)
        addSubview(valueLabel)

        // MARK: Layout
        label.snp.makeConstraints { (make) in
            make.leading.equalTo(self)
            make.centerY.equalTo(self)
        }

        slider.snp.makeConstraints { (make) in
            make.left.equalTo(label.snp.right).offset(8)
            make.centerY.equalTo(self)
        }

        valueLabel.snp.makeConstraints { (make) in
            make.left.equalTo(slider.snp.right).offset(8)
            make.right.equalTo(self)
            make.centerY.equalTo(self)
            make.width.equalTo(40)
            make.height.equalTo(self)
        }

        // MARK: Slider Value Changed
        self.slider.addTarget(self, action: #selector(sliderValueChanged(_:)), for: .valueChanged)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    @objc private func sliderValueChanged(_ sender: UISlider) {
        let newValue = Int32(sender.value)
        
        if let oldValueStr = self.valueLabel.text, let oldValue = Int32(oldValueStr) {
            if oldValue != newValue {
                self.valueLabel.text = String(newValue)
                self.onValueChanged?(newValue)
            }
        }
    }
}
