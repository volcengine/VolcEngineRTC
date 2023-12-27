//
//  GCDTimer.swift
//  ApiExample
//
//  Created by bytedance on 2023/10/13.
//  Copyright © 2021 bytedance. All rights reserved.
//

import Foundation

class GCDTimer {
    private var timer: DispatchSourceTimer?
    private var executionBlock: (() -> Void)?
    
    init(interval: DispatchTimeInterval, executionBlock: @escaping () -> Void) {
        self.executionBlock = executionBlock
        
        timer = DispatchSource.makeTimerSource(queue: DispatchQueue.global())
        timer?.schedule(deadline: .now(), repeating: interval)
        timer?.setEventHandler(handler: { [weak self] in
            self?.executionBlock?()
        })
    }
    
    func start() {
        timer?.resume()
    }
    
    func cancel() {
        timer?.cancel()
        timer = nil
        executionBlock = nil
    }
}
