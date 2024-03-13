//
//  BeautyBarView.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/31.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

protocol BeautyBarViewDelegate: NSObjectProtocol {
    func beautyBarView(barView: BeautyBarView, didClickedEffect model: EffectModel)
    func beautyBarView(barView: BeautyBarView, didChangeEffectValue model: EffectModel)
}

class BeautyBarView: UIView {
    
    weak var delegate: BeautyBarViewDelegate?
    
    var segment: UISegmentedControl!
    var sliderLabel: UILabel!
    var slider: UISlider!
    var buttonListView: UIView!
    
    var dataArray = [[EffectModel]]()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        self.backgroundColor = UIColor.white
        
        // segment
        segment = UISegmentedControl(items: BeautyModel.sectionList())
        segment.selectedSegmentIndex = 0
        segment.addTarget(self, action: #selector(segmentValueChanged), for: .valueChanged)
        self.addSubview(segment)
        segment.snp.makeConstraints { make in
            make.top.equalToSuperview()
            make.left.equalTo(20)
            make.right.equalTo(-20)
        }
        
        // sliderLabel
        sliderLabel = UILabel()
        sliderLabel.font = UIFont.systemFont(ofSize: 17)
        sliderLabel.text = "美颜强度"
        self.addSubview(sliderLabel)
        sliderLabel.snp.makeConstraints { make in
            make.left.equalTo(20)
            make.top.equalTo(segment.snp.bottom).offset(35)
        }
        
        // slider
        slider = UISlider()
        slider.addTarget(self, action: #selector(sliderValueChanged), for: .valueChanged)
        self.addSubview(slider)
        slider.snp.makeConstraints { make in
            make.centerY.equalTo(sliderLabel)
            make.left.equalTo(sliderLabel.snp.right).offset(30)
            make.right.equalTo(-20)
        }
        
        // buttonListView
        buttonListView = UIView()
        self.addSubview(buttonListView)
        buttonListView.snp.makeConstraints { make in
            make.left.equalTo(20)
            make.top.equalTo(segment.snp.bottom).offset(90)
            make.bottom.equalTo(self)
            make.right.equalTo(-20)
        }
        
        loadData()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    // MARK: - Private action
    @objc func buttonClicked(button: UIButton) {
        for case let subButton as EffectButton in buttonListView.subviews {
            if subButton == button {
                switch segment.selectedSegmentIndex {
                case 0:  //美颜
                    subButton.isSelected = true
                    subButton.model!.selected = true
                    slider.value = subButton.model!.value
                case 1:  //滤镜
                    subButton.isSelected = true
                    subButton.model!.selected = true
                    subButton.model!.value = 0
                    slider.value = subButton.model!.value
                case 2, 3:  //贴纸, 背景分割
                    subButton.isSelected = !subButton.isSelected
                    subButton.model!.selected = subButton.isSelected
                default:
                    // error
                    break
                }
                
                (delegate)?.beautyBarView(barView: self, didClickedEffect: subButton.model!)
            } else {
                subButton.isSelected = false
                subButton.model!.selected = false
            }
        }
    }
    
    
    @objc func segmentValueChanged(segment: UISegmentedControl) {
        let modelArray = dataArray[segment.selectedSegmentIndex]
        
        buttonListView.subviews.forEach { $0.removeFromSuperview() }
        
        for i in 0..<modelArray.count {
            let model = modelArray[i]
            let button = EffectButton()
            button.model = model
            
            button.addTarget(self, action: #selector(buttonClicked), for: .touchUpInside)
            
            buttonListView.addSubview(button)
            
            let row = i / 4
            let col = i % 4
            button.snp.makeConstraints { make in
                make.top.equalTo(row * (30 + 36))
                make.centerX.equalTo(buttonListView).multipliedBy(0.5 * CGFloat(col) + 0.25)
                make.width.equalTo(70)
                make.height.equalTo(36)
            }
        }
        
        switch segment.selectedSegmentIndex {
        case 0:  //美颜
            buttonListView.snp.updateConstraints { make in
                make.top.equalTo(segment.snp.bottom).offset(90)
            }
            sliderLabel.text = "美颜强度"
            sliderLabel.isHidden = false
            slider.isHidden = false
            
            if let button = buttonListView.subviews.first as? EffectButton {
                button.isSelected = true
                let model = modelArray[0]
                slider.value = Float(model.value)
            }
            
        case 1:  //滤镜
            buttonListView.snp.updateConstraints { make in
                make.top.equalTo(segment.snp.bottom).offset(90)
            }
            sliderLabel.text = "滤镜强度"
            sliderLabel.isHidden = false
            slider.isHidden = false
            
            var selected = false
            for case let button as EffectButton in buttonListView.subviews {
                if button.model!.selected {
                    button.isSelected = true
                    slider.value = Float(button.model!.value)
                    selected = true
                }
            }
            
            if !selected {
                //之前没有选中过,默认第一个
                if let button = buttonListView.subviews.first as? EffectButton {
                    button.isSelected = true
                    let model = modelArray[0]
                    slider.value = Float(model.value)
                }
            }
            
        case 2:  //贴纸
            buttonListView.snp.updateConstraints { make in
                make.top.equalTo(segment.snp.bottom).offset(36)
            }
            sliderLabel.isHidden = true
            slider.isHidden = true
            
            for case let button as EffectButton in buttonListView.subviews {
                button.isSelected = button.model!.selected
            }
            
        case 3:  //背景分割
            buttonListView.snp.updateConstraints { make in
                make.top.equalTo(segment.snp.bottom).offset(36)
            }
            sliderLabel.isHidden = true
            slider.isHidden = true
            
            var selected = false
            for case let button as EffectButton in buttonListView.subviews {
                if button.model!.selected {
                    button.isSelected = true
                    selected = true
                }
            }
            
            if !selected {
                //之前没有选中过,默认第一个
                if let button = buttonListView.subviews.first as? EffectButton {
                    button.isSelected = false
                }
            }
            
        default:
            break
        }
    }
    
    @objc func sliderValueChanged(slider: UISlider) {
        for case let button as EffectButton in buttonListView.subviews {
            if button.isSelected {
                button.model!.value = slider.value
                (delegate)?.beautyBarView(barView: self, didChangeEffectValue: button.model!)
            }
        }
    }
    
    func loadData() {
        var jsonList = [[Dictionary<String, Any>]]()
        jsonList.append(BeautyModel.beautyList())
        jsonList.append(BeautyModel.filterList())
        jsonList.append(BeautyModel.stickerList())
        jsonList.append(BeautyModel.virtualBackgroundList())
        
        for i in 0..<jsonList.count {
            let sectionList = jsonList[i]
            var modelList = [EffectModel]()
            for j in 0..<sectionList.count {
                let model = EffectModel()
                model.type = EffectModelType(rawValue: i)!
                model.selected = false
                model.value = 0
                model.name = sectionList[j]["name"] as? String
                model.key = sectionList[j]["key"] as? String
                model.subType = sectionList[j]["subType"] as? EffectModelSubType
                modelList.append(model)
            }
            dataArray.append(modelList)
        }
        
        segmentValueChanged(segment: segment)
    }
    
}
