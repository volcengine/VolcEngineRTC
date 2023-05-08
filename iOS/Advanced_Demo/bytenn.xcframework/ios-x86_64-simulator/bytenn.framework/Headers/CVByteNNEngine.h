// Copyright (C) 2020 Beijing Bytedance Network Technology Co., Ltd. All rights reserved.
#ifndef _CV_BYTENN_ENGINE_H_
#define _CV_BYTENN_ENGINE_H_

#include "ByteNNBasicType.h"
#include <memory>

namespace BYTENN {

    class ByteNNAsyncOutputListener {
    public:
        virtual void OnData(std::vector <Tensor> *outTensors) const = 0;

        virtual void OnEvent(NNErrorCode errorCode, const char *errorMsg = nullptr) const = 0;

        virtual ~ByteNNAsyncOutputListener() {}
    };

    class ByteNNEngine {
    public:
        virtual ~ByteNNEngine();

        // inference interfaces
        virtual NNErrorCode Init(const Config &config) = 0;

        virtual NNErrorCode SetInput(const std::vector <Tensor> &inTensors) = 0;

        virtual NNErrorCode GetInputConfig(std::vector <Tensor> &inTensors) = 0;

        virtual NNErrorCode Inference() = 0;

        virtual NNErrorCode ReInferShape(int height, int width) = 0;

        virtual NNErrorCode ReInferShape(const std::vector <Tensor> &inTensors) = 0;

        virtual NNErrorCode GetOutput(std::vector<Tensor> *outTensors) = 0;

        virtual void Release() = 0;

        virtual NNErrorCode SetAsyncOutputListener(std::shared_ptr <ByteNNAsyncOutputListener> listener) = 0;

        virtual ForwardType GetForwardType() = 0;

        virtual NNErrorCode Init(const ConfigExt &extendedConfig) = 0;

        virtual NNErrorCode SetInput(const std::vector <std::shared_ptr<TensorExt> > &inTensorsExt) = 0;

        virtual NNErrorCode GetInputConfig(std::vector <std::shared_ptr<TensorExt> > &inTensorsExt) = 0;

        virtual NNErrorCode SetOutput(const std::vector <std::shared_ptr<TensorExt> > &outTensorsExt) = 0;

        virtual NNErrorCode GetOutput(std::vector<std::shared_ptr<TensorExt> > *outTensorsExt) = 0;

        virtual NNErrorCode Inference(const std::string &modelName) = 0;

        virtual NNErrorCode ClearState() = 0;

        virtual NNErrorCode ReInferShape(int num, int height, int width,  std::string name) = 0;

        // on-device training interfaces
        virtual NNErrorCode SetLabel(const std::vector <Tensor> &lables) = 0;

        virtual NNErrorCode GetLabel(const std::vector <std::string> &layerNames, std::vector<Tensor> *labels) = 0;

        virtual NNErrorCode SetOptimizer(OptimizerType optType, float learningRate,
                                        const std::vector <std::string> &trainableLayers) = 0;

        virtual NNErrorCode Step(float* loss) = 0;

        virtual NNErrorCode SaveModel(void *modelBuffer) = 0;

        virtual NNErrorCode SetWeight(const Tensor &weightTensor) = 0;

        virtual NNErrorCode GetWeight(const std::string &weightName, Tensor *weightTensor) = 0;

        virtual NNErrorCode GetGradient(const std::string &gradientName, Tensor *gradientTensor) = 0;

        virtual NNErrorCode SetLossLayer(const std::vector <LossInfo>& lossLayers) = 0;
    };

    class CVEngineFactory {
    public:
        // offline check
        __attribute__((visibility("default")))
        static std::shared_ptr <ByteNNEngine> Create(const char* licenseBuffer, const unsigned long length, const unsigned int func_id, 
                                    unsigned int* sub_funcs, const char* app_id, int* error_code);

        // online check
        __attribute__((visibility("default")))
        static std::shared_ptr <ByteNNEngine> Create(const char* licenseBuffer, const unsigned long length, const unsigned int func_id, 
                                    unsigned int* sub_funcs, int* error_code);

        __attribute__((visibility("default")))
        static int get_auth_msg(char** auth_msg, int *length);

#if defined(__ANDROID__) || defined(TARGET_OS_ANDROID)
        // used for getting android device id, call this BEFORE Creating bytenn engine
        __attribute__((visibility("default")))
        static int set_jvm(void* jvm);
#endif
    };

    class ByteNNUtils {
    public:
        static std::string GetVersion();

        static NNErrorCode GetDeviceInfo(const std::string &deviceType, std::vector <std::string> &deviceInfo);

        static void ByteNNSystemSettings(const SystemSetting &settings);

        static NNErrorCode GetRunningDevice(const std::string &deviceType, std::string &deviceInfo);// some device has multipule gpus, return the running type
        
        static NNErrorCode SetRunningDevice(const std::string &deviceType, const std::string &deviceName);// some device has multipule gpus, set the desired gpu type

        static bool SupportDeviceIO(const DeviceIOType &type);
    };

    std::string GetVersion(); // Warning:GetVersion() is deprecated. Please use ByteNNUtils::GetVersion().
} // namespace BYTENN

#endif //_CV_BYTENN_ENGINE_H_