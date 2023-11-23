//#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#define  MAX_NAMA_BUNDLE_NUM 1
//extern const std::string g_fuDataDir;
extern const std::string g_v3Data;

const std::string g_faceBeautification = "/graphics/face_beautification.bundle";

const std::string g_Makeup = "/graphics/face_makeup.bundle";

const std::string g_NewFaceTracker = "/new_face_tracker.bundle"; //δ�ҵ�

const std::string g_gestureRecongnition = "/heart.bundle"; //δ�ҵ�

const std::string g_anim_model = "/anim_model.bundle"; //δ�ҵ�

const std::string g_ardata_ex = "/ardata_ex.bundle"; //δ�ҵ�

const std::string g_fxaa = "/graphics/fxaa.bundle";

const std::string g_tongue = "/graphics/tongue.bundle";

const std::string g_ai_faceprocessor = "/model/ai_face_processor_pc.bundle";

const std::string g_ai_landmark239 = "/AI_model/ai_facelandmarks239.bundle"; //δ�ҵ�

std::string faceBeautyParamName[] = { "blur_level","color_level", "red_level", "eye_bright", "tooth_whiten" }; //δ�ҵ�


std::string getExePath();

#endif // !CONFIG_H
