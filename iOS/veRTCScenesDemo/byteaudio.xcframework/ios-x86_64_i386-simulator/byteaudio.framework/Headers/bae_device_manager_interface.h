#pragma once

#ifdef WIN32
#define BYTEAUDIO_API __declspec(dllexport)
#else
#define BYTEAUDIO_API __attribute__((__visibility__("default")))
#endif

#include <stdint.h>

#include <string>

namespace bae {

class IByteAudioDeviceManager {
public:
    /**
     * @brief Get a shared intance of IByteAudioEngine.
     * @return pointer of IByteAudioEngine
     */
    static IByteAudioDeviceManager* get_device_manager_instance();

    /**
     * @brief Get num of playout devices on Win/Mac platform.
     * @return num of playout devices
     */
    virtual int playout_devices() = 0;

    /**
     * @brief Get num of record devices on Win/Mac platform.
     * @return num of record devices
     */
    virtual int recording_devices() = 0;

    /**
     * @brief Get playout device name of the index on Win/Mac platform.
     * @param [in] index: index of device
     * @param [out] name
     * @param [out] guid
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int playout_device_name(int index, std::string& name, std::string& guid) = 0;

    /**
     * @brief Get record device name of the index.
     * @param [in] index: index of device
     * @param [out] name
     * @param [out] guid
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int recording_device_name(int index, std::string& name, std::string& guid) = 0;

    /**
     * @brief Set playout device on Win/Mac platform.
     * @param [in] index: index of device
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_playout_device(int index) = 0;

    /**
     * @brief Get current playout device on Win/Mac platform.
     * @param [out] name
     * @param [out] guid
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int get_playout_device(std::string& name, std::string& guid) = 0;

    /**
     * @brief Test playout device for usability by trying to init playout device.
     * @param [in] guid: guid of device
     * @return error code of check result.
     *         kByteAudioSuccess: deivce test success.
     *         other: device check failed, refer to @ByteAudioErrorCode.
     */
    virtual int init_playout_device_for_test(const std::string& guid) = 0;

    /**
     * @brief Set record device on Win/Mac platform.
     * @param [in] index: index of device
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_recording_device(int index) = 0;

    /**
     * @brief Get current recording device on Win/Mac platform.
     * @param [out] name
     * @param [out] guid
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int get_recording_device(std::string& name, std::string& guid) = 0;

    /**
     * @brief Test recording device for usability by trying to init recording device.
     * @param [in] guid: guid of device
     * @return error code of check result.
     *         kByteAudioSuccess: deivce test success.
     *         other: device check failed, refer to @ByteAudioErrorCode.
     */
    virtual int init_recording_device_for_test(const std::string& guid) = 0;

    /**
     * @brief Set the volume of the speaker device on Win/Mac platform.
     * @param [in] volume: volume of the speaker device, ranges between 0 ~ 255.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_speaker_volume(int volume) = 0;

    /**
     * @brief Retrieves the volume of the speaker device on Win/Mac platform.
     * @param [out] volume: Pointer to the speaker device volume, ranges between 0 ~ 255.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int speaker_volume(int* volume) = 0;

    /**
     * @brief Set the volume of the microphone on Win/Mac platform.
     * @param [in] volume: volume of the microphone, ranges between 0 ~ 255.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_microphone_volume(int volume) = 0;

    /**
     * @brief Retrieves the volume of the microphone on Win/Mac platform.
     * @param [out] volume: Pointer to the microphone volume, ranges between 0 ~ 255.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int microphone_volume(int* volume) = 0;

    /**
     * @brief Whether mutes the speaker device on Win/Mac platform.
     * @param [in] mute: Sets whether to mute/unmute speaker device.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_speaker_mute(bool mute) = 0;

    /**
     * @brief Retrieves the mute status of the speaker device on Win/Mac platform.
     * @param [out] muted: Pointer to whether the speaker device is muted/unmuted.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int speaker_mute(bool* muted) const = 0;

    /**
     * @brief Whether mutes the microphone of device on Win/Mac platform.
     * @param [in] mute: Sets whether to mute/unmute microphone of device.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int set_microphone_mute(bool mute) = 0;

    /**
     * @brief Retrieves the mute status of the microphone of device on Win/Mac platform.
     * @param [out] muted: Pointer to whether the microphone of device is muted/unmuted.
     * @return error code, refer to @ByteAudioErrorCode
     */
    virtual int microphone_mute(bool* muted) const = 0;
};

BYTEAUDIO_API IByteAudioDeviceManager* get_device_manager_instance();
}  // namespace bae
