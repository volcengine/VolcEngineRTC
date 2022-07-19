#ifndef     BEF_AI_IMAGE_QUALITY_ENHANCEMENT_COMMON_FUNCTION_H
#define     BEF_AI_IMAGE_QUALITY_ENHANCEMENT_COMMON_FUNCTION_H

#include "bef_ai_image_quality_enhancement_public_define.h"
#include "bef_ai_image_quality_enhancement_private_define.h"


int checkLicense(bef_image_quality_enhancement_handle handle, const char* handleType, const char* licensePath, bool onlineLicense = false);
int init(const char* handle_type,LensAlgorithmType type,bef_image_quality_enhancement_handle* handle,void* config,std::function<int(ILensFlowGraphInterface* flowGraph,void* config)> func);
int getFlowGraphPtr(bef_image_quality_enhancement_handle handle, ILensFlowGraphInterface **graph, const char* handleType);
int destoryHandle(bef_image_quality_enhancement_handle handle, const char* handleType);

#endif 
