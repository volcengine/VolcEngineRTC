//
//  ToastComponents.swift
//  ApiExample
//
//  Created by bytedance on 2023/11/3.
//  Copyright © 2021 bytedance. All rights reserved.
//

import UIKit
import SnapKit

class ToastComponents {

    weak var keepToastView: ToastView?

    static let shared = ToastComponents()

    private init() { }

    func show(withMessage message: String, inView windowView: UIView, keep: Bool, block: @escaping ((Bool) -> Void)) {
        guard message.count > 0 else { return }
        if keep && keepToastView != nil {
            return
        }
        DispatchQueue.main.async { [weak self] in
            let toastView = ToastView(message: message)
            windowView.addSubview(toastView)
            toastView.snp.makeConstraints { make in
                make.center.equalTo(windowView)
            }
            if keep {
                self?.keepToastView = toastView
            } else {
                DispatchQueue.main.asyncAfter(deadline: .now() + 2) {
                    toastView.removeFromSuperview()
                }
            }
            block(true)
        }
    }

    func show(withMessage message: String, inView windowView: UIView, block: @escaping ((Bool) -> Void)) {
        show(withMessage: message, inView: windowView, keep: false, block: block)
    }

    func show(withMessage message: String, inView windowView: UIView) {
        show(withMessage: message, inView: windowView, block: { _ in })
    }
    
    func show(withMessage message: String) {
        DispatchQueue.main.async { [weak self] in
            let windowView = UIApplication.shared.keyWindow
            self?.show(withMessage: message, inView: windowView!)
        }
    }

    func show(withMessage message: String, delay: TimeInterval) {
        if delay > 0 {
            DispatchQueue.main.asyncAfter(deadline: .now() + delay) {
                self.show(withMessage: message)
            }
        } else {
            show(withMessage: message)
        }
    }

    func dismiss() {
        keepToastView?.removeFromSuperview()
        keepToastView = nil
    }
}
