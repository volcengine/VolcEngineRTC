// Copyright (C) 2020 Beijing Bytedance Network Technology Co., Ltd. All rights reserved.
#ifndef __BYTENN_BASIC_TYPE_H__
#define __BYTENN_BASIC_TYPE_H__

#include <vector>
#include <string>
#include <functional>
#include <map>

namespace BYTENN {
    enum class DataFormat {
        NCHW = 0,
        NHWC = 1,
    };

    enum class DataType {
        U8 = 0,
        Int8 = 1, //Support Int8 on CPU across Android/iOS/Mac/Windows and pixelbuffer on Mac and iOS
        Int16 = 2,
        Uint16 = 3,
        Float = 4,
        Fp16 = 5,
        Double = 6,
    };

    enum class NNErrorCode {
#if !defined(NO_ERROR)
        NO_ERROR = 0,
#endif
        SUCCESS = 0,
        ERR_MEMORY_ALLOC = 1,
        NOT_IMPLEMENTED = 2,
        ERR_UNEXPECTED = 3,
        ERR_DATANOMATCH = 4,
        INPUT_DATA_ERROR = 5,
        CALL_BACK_STOP = 6,
        BACKEND_FALLBACK = 7,
        NULL_POINTER = 8,
        INVALID_POINTER = 9,
        INVALID_MODEL = 10,
        INFER_SIZE_ERROR = 11,
        NOT_SUPPORT = 12,
        DESTROYED_ERROR = 13,
        WRONG_LICENSE = 14,
        BROKEN_MODEL = 15,
        EARLY_STOP = 16,
    };

    enum class ForwardType {
        CPU,  // Android, iOS, Mac, Windows and Linux
        GPU,  // Android, iOS, Mac, Windows
        DSP,  // Android, iOS
        NPU,  // Android
        Auto, // Android, iOS, Mac, Windows and Linux

        METAL,  // iOS
        OPENCL, // Android, Mac, Windows
        OPENGL,
        VULKAN,
        CUDA,   // Windows, Linux
        CoreML, // iOS and Mac
    };

    enum class OptimizerType : uint8_t {
        SGD = 0,
        // TODO
        RMSProp,
        ADAM,
        ADAMW
    };

    enum class TextureFormat
    {
        RGBA = 0,
        RGB = 1,
        RG = 2,
        R = 3,
    };

    enum class DeviceIOType
    {
        ByteNN_CPUBuffer = 0,
        ByteNN_GLTexture = 1,
        ByteNN_CLImage = 2,
        ByteNN_CLBuffer = 3,
        ByteNN_CVPixelBuffer = 4,
        ByteNN_MTLTexture = 5,
        ByteNN_MTLBuffer = 6,
        ByteNN_CUDABuffer = 7,
        ByteNN_AhardwareBuffer = 8,
        ByteNN_IONBuffer = 9,
        ByteNN_ExtendedBuffer = 10,
    };

    struct Config {
        ForwardType type = ForwardType::Auto;
        const unsigned char *modelBuffer = NULL;
        int modelBufferSize;
        bool doModelValidation = false;

        int numThread = 1;                        // Only support 1 or 2 threads in the CPU backend
        std::string oclKernelBinPath = "./";      // cachePath
        std::string runtimeLibLoadingPath = "./"; // runtimePath
        std::vector <std::string> inputNames;
        std::vector <std::string> outputNames;
        std::string modelName = "";
        void *extend = nullptr;
        std::vector <uint8_t> license;

        enum PowerMode {
            NormalPower = 0,
            HighPower,
            LowPower
        };
        PowerMode power = PowerMode::HighPower;

        enum PrecisionMode {
            NormalPrecision = 0,
            HighPrecision,
            LowPrecision
        };

        PrecisionMode precision = PrecisionMode::NormalPrecision;

        static std::function<void(int, const std::string &, const std::string &)> mLogCallback;

    };

    struct ConfigExt: public Config{
        std::map<std::string, const unsigned char *> models;
        std::vector<BYTENN::DataType> inDeviceTensorDataTypes;
        std::vector<BYTENN::DataType> outDeviceTensorDataTypes;
        std::vector<BYTENN::DeviceIOType> inDeviceTensorTypes;
        std::vector<BYTENN::DeviceIOType> outDeviceTensorTypes;
        void *context=nullptr; // Metal: MTLDevice, OpenCL: cl_context ...
        void *cmdque = nullptr;
        virtual ~ConfigExt();
    };

    class Tensor {
    public:
        size_t GetDataCount() const;

        size_t GetByteSize() const;

        void *raw_data;
        DataFormat format = DataFormat::NHWC;
        DataType data_type;
        int batch = 1;
        int height = 1;
        int width = 1;
        int channel = 1;
        int fraction = 0;
        std::string name;
    };

    class SystemSetting {
    public:
        std::string cachePath;
        std::string runtimePath;
    };

    class LossInfo{
    public:
        std::vector<std::string> bottom_layers;
        std::string loss_type;
        std::string loss_name;
        std::string extra_info;
        virtual ~LossInfo() {}
    };

    class TensorExt: public Tensor {
    public:
        TextureFormat textureFormat = TextureFormat::RGBA;
        DeviceIOType deviceIOType   = DeviceIOType::ByteNN_GLTexture;
        void* devicePtr = nullptr;
        int textureID = 0;

        float scale = 0.0; // Asymmetric quantize Info
        int zero = 0;
        virtual ~TensorExt();
    };

    using ByteNNDataFormat = DataFormat;
    using ByteNNDataType = DataType;
    using ByteNNConfig = Config;
} // namespace BYTENN

#endif //__BYTENN_BASIC_TYPE_H__
