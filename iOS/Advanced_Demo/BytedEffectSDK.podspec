Pod::Spec.new do |spec|
  spec.name         = 'BytedEffectSDK'
  spec.version      = '4.3.2' // 需要对齐 CV SDK 的版本
  spec.summary      = 'Demo for effect-sdk'
  spec.description  = 'Demo for effect-sdk'
  spec.homepage     = 'https://github.com/volcengine'
  spec.license      = { :type => 'Copyright', :text => 'Bytedance copyright' }
  spec.author       = { 'bytertc' => 'bytertc@bytedance.com' }
  spec.source       = { :path => './'}
  spec.ios.deployment_target = '9.0'
  spec.vendored_frameworks = 'effect-sdk.framework'
  spec.requires_arc = true
  spec.libraries = 'stdc++', 'z'
  spec.frameworks   = 'Accelerate','AssetsLibrary','AVFoundation','CoreGraphics','CoreImage','CoreMedia','CoreVideo','Foundation','QuartzCore','UIKit','CoreMotion'
  spec.weak_frameworks = 'Metal','MetalPerformanceShaders', 'Photos', 'CoreML'
 
#  spec.resources = ['Resource/*.{bundle}']
end
