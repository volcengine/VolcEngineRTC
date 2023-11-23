#ifndef CNAMASDKSCENE_H
#define CNAMASDKSCENE_H

#include "CNamaSDK.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * global api
 */

/**
 \brief use binary shader program or not.
 \param enable > 0 means use binary shader program, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableBinaryShaderProgram(int enable);

/**
 \brief Specify directory for saving and loading binary shader program.
 \param path is directory path
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetBinaryShaderProgramDirectory(const char* path);

/*
 * create, destroy, bind, and unbind api
 */

/**
 \brief Create a new scene.
 \return an unsigned integer handle representing the scene.
*/
FUNAMA_API unsigned int fuCreateScene();

/**
 \brief Destroy the target scene.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuDestroyScene(unsigned int handle_id);

/**
 \brief Set the target scene for render.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetCurrentScene(unsigned int handle_id);

/**
 \brief Bind items to the target scene
 \param handle_id is the target scene handle
 \param p_items points to a list of item handles to be bind to the target
 scene
 \param n_items is the number of item handles in p_items
 \return the number of items successfully bound to the target scene
*/
FUNAMA_API int fuBindItemsToScene(unsigned int handle_id, int* p_items,
                                  int n_items);

/**
 \brief Unbind items from the target scene
 \param handle_id is the target scene handle
 \param p_items points to a list of item handles to be unbind from the target
 scene
 \param n_items is the number of item handles in p_items
 \return the number of items successfully unbound from the target scene
*/
FUNAMA_API int fuUnbindItemsFromScene(unsigned int handle_id, int* p_items,
                                      int n_items);

/**
 \brief Create an instance for a target scene.
 \param handle_id is the target scene handle
 \return an unsigned integer handle representing the instance.
*/
FUNAMA_API unsigned int fuCreateInstance(unsigned int handle_id);

/**
 \brief Destroy the target instance.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuDestroyInstance(unsigned int handle_id);

/**
 \brief Bind items to the target instance
 \param handle_id is the target instance handle
 \param p_items points to a list of item handles to be bind to the target
 instance
 \param n_items is the number of item handles in p_items
 \return the number of items successfully bound to the instance
*/
FUNAMA_API int fuBindItemsToInstance(unsigned int handle_id, int* p_items,
                                     int n_items);

/**
 \brief Unbind items from the target instance
 \param handle_id is the target instance handle
 \param p_items points to a list of item handles to be unbind from the target
 instance
 \param n_items is the number of item handles in p_items
 \return the number of items successfully unbound from the instance
*/
FUNAMA_API int fuUnbindItemsFromInstance(unsigned int handle_id, int* p_items,
                                         int n_items);
/*
 * render related api
 */
/**
 \brief Enable or not render for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means render, enable <= 0 means not render
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableRender(unsigned int handle_id, int enable);

/*
 * ground reflection related api
 */
/**
 \brief Enable or not render ground reflection for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means render ground reflection, enable <= 0 means not render
 ground reflection \return zero for failed, one for success
*/
FUNAMA_API int fuEnableGroundReflection(unsigned int handle_id, int enable);

/*
 * ground reflection related parameter
 */
/**
 \brief set parameters to ground reflection.
 \param handle_id is the target scene handle
 \param maxTrans > 0 means the max transparency for flip scene;
 \param maxDis > 0 means the distance flip scene to fade;
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetGroundReflectionPrameters(unsigned int handle_id,
                                              float maxTrans, float maxDis);

/*
 * dof related api
 */
/**
 \brief set dof parameters to camera.
   \param enable > 0 means open dof, enable <= 0 means close dof
 \return zero for failed, one for success
*/

FUNAMA_API int fuEnableDof(unsigned int handle_id, int enable);

/*
 * dof related api
 */
/**
 \brief set dof parameters to camera.
 \param enable is a coc visual swith;
 \return zero for failed, one for success
*/

FUNAMA_API int fuEnableDofDebug(unsigned int handle_id, int enable);

/*
 * dof related api
 */
/**
 \brief set dof parameters to camera.
 \param handle_id is the target scene handle
 \param focalLength,focusDistance,maxCoC,aperture is physical camera parameters;
 \param blurSize contain(0->smacll, 1->medium, 2->large, 3->verylarge);
 \return zero for failed, one for success
*/

FUNAMA_API int fuSetDofParamters(unsigned int handle_id, float focalLength,
                                 float focusDistance, float maxCoC,
                                 float aperture, int blurSize);

/*
 * bloom related api
 */
 /**
  \brief set bloom parameters to postprocess.
    \param enable > 0 means open dof, enable <= 0 means close bloom
  \return zero for failed, one for success
 */

FUNAMA_API int fuEnableBloom(unsigned int handle_id, int enable);

/*
 * dof related api
 */
 /**
  \brief set Bloom parameters to postprocess.
  \param handle_id is the target scene handle
  \param threshold_value is the height-light threshold value;
  \param bloom_intensity control the effect of the high-light;
  \return zero for failed, one for success
 */

FUNAMA_API int fuSetBloomParamters(unsigned int handle_id, float threshold_value, float bloom_intensity);

/**
 \brief Enable or not render camera for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means render, enable <= 0 means not render
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableRenderCamera(unsigned int handle_id, int enable);

/**
 \brief Enable or not use pure background color for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableBackgroundColor(unsigned int handle_id, int enable);

/**
 \brief Set background rgba color for the target scene.
 \param handle_id is the target scene handle
 \param r is color of R channel, from 0 to 255
 \param g is color of G channel, from 0 to 255
 \param b is color of B channel, from 0 to 255
 \param a is color of A channel, from 0 to 255
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetBackgroundColor(unsigned int handle_id, int r, int g, int b, int a);

/**
 \brief Enable or not main light shadow for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableShadow(unsigned int handle_id, int enable);

/**
 \brief Set main light shadow map size for the target scene.
 \param handle_id is the target scene handle
 \param size
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetShadowMapSize(unsigned int handle_id, int size);

/**
 \brief Set main light shadow bias for the target scene.
 \param handle_id is the target scene handle
 \param uniform_bias, is 0.01 defaultly
 \param normal_bias, is 0.1 defaultly
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetShadowBias(unsigned int handle_id, float uniform_bias,
                               float normal_bias);

/**
 \brief Set instance main light shadow PCF level
 \param handle_id is the target instance handle
 \param level = 0, 1, 2
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceShadowPCFLevel(unsigned int handle_id, int level);

/**
 \brief Set instance main light shadow map sample offset scale.
 \param handle_id is the target instance handle
 \param offset_scale is sample offset scale
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceShadowSampleOffset(unsigned int handle_id,
                                               int offset_scale);

/**
 \brief Enable or not bloom for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableBloom(unsigned int handle_id, int enable);

/**
 \brief Enable use or not low quality lighting for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableLowQualityLighting(unsigned int handle_id, int enable);

/**
 \brief Enable use or not low resolution texture for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableLowResolutionTexture(unsigned int handle_id, int enable);

/**
 \brief Enable HDR RGBA16F for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use HDR RGBA16F, enable <= 0 means use R11FG11FB10F
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableHDRRGBA16F(unsigned int handle_id, int enable);

/*
 * ai related api
*/
FUNAMA_API int fuEnableFaceProcessor(unsigned int handle_id, int enable);

/**
 \brief Turn on or off ar mode for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableARMode(unsigned int handle_id, int enable);

/**
 \brief Set instance input camera buffer matrix, for transforming fuai result
 \param handle_id is the target instance handle
 \param mat  the transform matrix use to transform the input
 cpu buffer
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceInputCameraBufferMatrix(unsigned int handle_id,
                                                    TRANSFORM_MATRIX mat);

/**
 \brief Set instance face id of face processor.
 \param handle_id is the target instance handle
 \param value is face id
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFaceProcessorFaceId(unsigned int handle_id,
                                                int value);

/**
 \brief Set instance face processor type.
 \param handle_id is the target instance handle
 \param type is face processor type,  1 : use inner face processor, 2 : use
 outer face data result \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFaceProcessorType(unsigned int handle_id, int type);

/**
 \brief Set instance face processor outer data ptr.
 \param handle_id is the target instance handle
 \param void* is pointer to FaceProcessorResult
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFaceProcessorOuterResultPtr(unsigned int handle_id,
                                                        void* ptr);

/**
 \brief Set instance filter size of face processor.
 \param handle_id is the target instance handle
 \param filter_size_rotaion is filter size of head rotation
 \param filter_size_translation is filter size of head translation
 \param filter_size_eye_rotaion is filter size of eye rotation
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFaceProcessorFilterSize(
    unsigned int handle_id, int filter_size_rotaion,
    int filter_size_translation, int filter_size_eye_rotation);

/**
 \brief Reset instance filter of face processor.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetInstanceFaceProcessorFilter(unsigned int handle_id);

/**
 \brief Set instance head rotation deltaX of face processor.
 \param handle_id is the target instance handle
 \param value is x delta rotation
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceHeadRotationDeltaX(unsigned int handle_id,
                                               float value);

/**
 \brief Set instance head rotation Z Range of face processor.
 \param handle_id is the target instance handle
 \param min_angle default is -180
 \parma max_angle default is 180
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceHeadRotationZRange(unsigned int handle_id,
                                               float min_angle,
                                               float max_angle);

/**
 \brief Set instance eye rotation deltaX of face processor.
 \param handle_id is the target instance handle
 \param value is x delta rotation
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceEyeRotationDeltaX(unsigned int handle_id,
                                              float value);

/**
 \brief Enable instance rotate head or not.
 \param handle_id is the target instance handle
 \param enable > 0 means enalbe blend , enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceFaceProcessorRotateHead(unsigned int handle_id,
                                                       int enable);

/**
 \brief Open or close the human anim driver for the target instance.
 \param handle_id is the target instance handle
 \param enable > 0 means open, enable <= 0 means close
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceEnableHumanAnimDriver(unsigned int handle_id,
                                                  int enable);

/**
 \brief Open or close AI human processor for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means open, enable <= 0 means close
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableHumanProcessor(unsigned int handle_id, int enable);


/**
 \brief set human processor 3D scene.
 \param handle_id is the target scene handle
 \param scene = 0 means selfie, enable > 0 means dance
 \return zero for failed, one for success
*/
FUNAMA_API int fuHumanProcessorSet3DScene(unsigned int handle_id, int scene);

/**
 \brief Open or close RiggingBVHInputProcessor for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means open, enable <= 0 means close
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableRiggingBVHInputProcessor(unsigned int handle_id,
                                                bool enable);

/**
 \brief Open or close hand detetor for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means open, enable <= 0 means close
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableHandDetetor(unsigned int handle_id, int enable);

/*
 * camera animation
 */

/**
 \brief Enable use camera aniamtion for the target scene or not.
 \param handle_id is the target scene handle
 \param enable > 0 means use, enable <= 0 means not use
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableCameraAnimation(unsigned int handle_id, int enable);

/**
 \brief Play target camera animation for the target scene.
 \param handle_id is the target scene handle
 \param anim_handle is target animation item handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPlayCameraAnimation(unsigned int handle_id, int anim_handle);

/**
 \brief Play target camera animation once for the target scene.
 \param handle_id is the target scene handle
 \param anim_handle is target animation item handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPlayCameraAnimationOnce(unsigned int handle_id,
                                         int anim_handle);

/**
 \brief Start or continue current camera animation for the target scene.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuStartCameraAnimation(unsigned int handle_id);

/**
 \brief Pause current camera animation for the target scene.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPauseCameraAnimation(unsigned int handle_id);

/**
 \brief Restart current camera animation for the target scene.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetCameraAnimation(unsigned int handle_id);

/**
 \brief Set camera animation transition time for the target scene.
 \param handle_id is the target scene handle
 \param time is transition time, second
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetCameraAnimationTransitionTime(unsigned int handle_id,
                                                  float time);

/**
 \brief Enable camera aniamtion internal lerp for the target scene or not.
 \param handle_id is the target scene handle
 \param enable > 0 means enable, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableCameraAnimationInternalLerp(unsigned int handle_id,
                                                   int enable);

/*
 * time updating releated api
 */

/**
 \brief Switch to system background, pause time update for the target scene
 \param handle_id is the target scene handle
 \param enable > 0 means switch to system background, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuPauseTimeUpdate(unsigned int handle_id, int enable);

/**
 \brief Enable control system time updating or not for the target scene
 \param handle_id is the target scene handle
 \param enable > 0 means control time byself, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableControlTimeUpdate(unsigned int handle_id, int enable);

/**
 \brief Set current time to control system time updating for the target scene
 \param handle_id is the target scene handle
 \param value is current in seconds
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetCurrentTime(unsigned int handle_id, float value);

/*
 * instance related api
 */

/**
 \brief Enable instance visible or not.
 \param handle_id is the target instance handle
 \param visible > 0 means visible, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceVisible(unsigned int handle_id, int visible);

/**
 \brief Enable instance single mesh visible or not.
 \param handle_id is the target instance handle
 \param mesh_handle is target mesh item handle
 \param visible > 0 means visible, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceSingleMeshVisible(unsigned int handle_id,
                                                 int mesh_handle, int visible);

/**
 \brief Enable instance use face beauty custom order or not.
 \param handle_id is the target instance handle
 \param enable > 0 means use custom order, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceUseFaceBeautyOrder(unsigned int handle_id,
                                                  int enable);

/**
 \brief Set instance face beauty custom order.
 \param handle_id is the target instance handle
 \param value points to an array of ints
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFaceBeautyOrder(unsigned int handle_id, int* value,
                                            int n);

/**
 \brief Set instance body visible list.
 \param handle_id is the target instance handle
 \param value points to an array of ints
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceBodyVisibleList(unsigned int handle_id, int* value,
                                            int n);
/**
 \brief Set instance body invisible list.
 \param handle_id is the target instance handle
 \param value points to an array of ints
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceBodyInvisibleList(unsigned int handle_id,
                                              int* value, int n);

/**
 \brief Enable instance hide neck or not.
 \param handle_id is the target instance handle
 \param enable > 0 means hide neck, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceHideNeck(unsigned int handle_id, int enable);

/**
 \brief Reset instance head to default.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetInstanceHead(unsigned int handle_id);

/**
 \brief Turn on or off instance facepup mode.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceFacepupMode(unsigned int handle_id, int enable);

/**
 \brief Set instance facepup value.
 \param handle_id is the target instance handle
 \param name is the parameter name
 \param value is the parameter value to be set
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFacepup(unsigned int handle_id, const char* name,
                                    float value);

/**
 \brief Set instance skeleton deformation.
 \param handle_id is the target instance handle
 \param name is the parameter name
 \param value is the parameter value to be set
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceDeformation(unsigned int handle_id,
                                        const char* name, float value);

/**
 \brief Set instance skeleton deformation rotation.
 \param handle_id is the target instance handle
 \param name is the skeleton name
 \param angle_x is euler angle x
 \param angle_y is euler angle y
 \param angle_z is euler angle z
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceDeformationRotation(unsigned int handle_id,
                                                const char* name, float angle_x,
                                                float angle_y, float angle_z);

/**
 \brief Set instance skeleton deformation translation.
 \param handle_id is the target instance handle
 \param name is the skeleton name
 \param x is the translation x
 \param y is the translation y
 \param z is the translation z
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceDeformationTranslation(unsigned int handle_id,
                                                   const char* name, float x,
                                                   float y, float z);

/**
 \brief Set instance skeleton deformation scale.
 \param handle_id is the target instance handle
 \param name is the skeleton name
 \param x is the scale x
 \param y is the scale y
 \param z is the scale z
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceDeformationScale(unsigned int handle_id,
                                             const char* name, float x, float y,
                                             float z);

/**
 \brief Enable instance expression blend or not.
 \param handle_id is the target instance handle
 \param enable > 0 means enalbe blend , enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceExpressionBlend(unsigned int handle_id,
                                               int enable);

/**
 \brief Set instance blend expression array.
 \param handle_id is the target instance handle
 \param value points to an array of floats
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceBlendExpression(unsigned int handle_id,
                                            float* value, int n);

/**
 \brief Set instance blend expression weight.
 \param handle_id is the target instance handle
 \param value points to an array of floats
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceExpressionWeight0(unsigned int handle_id,
                                              float* value, int n);

/**
 \brief Set instance default expression(face processor or animation) weight.
 \param handle_id is the target instance handle
 \param value points to an array of floats
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceExpressionWeight1(unsigned int handle_id,
                                              float* value, int n);

/**
 \brief Set instance uv anim frame id array.
 \param handle_id is the target instance handle
 \param value points to an array of Ints
 \param n specifies the number of elements in value
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceUVAnimArray(unsigned int handle_id, int* value, int n);

/**
 \brief Enable instance focus eye to camera or not.
 \param handle_id is the target scene handle
 \param enable > 0 means focus eye to camera, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceFocusEyeToCamera(unsigned int handle_id,
                                                int enable);

/**
 \brief Set instance focus eye to camera params
 \param handle_id is the target scene handle
 \param height_adjust is height adjust delta
 \param distance_adjust is distance adjust delta
 \param weight is weight
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFocusEyeToCameraParams(unsigned int handle_id,
                                                   float height_adjust,
                                                   float distance_adjust,
                                                   float weight);

/**
 \brief set instance rotation delta.
 \param handle_id is the target instance handle
 \param value is rotation delta
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceRotDelta(unsigned int handle_id, float value);

/**
 \brief Set instance scale delta.
 \param handle_id is the target instance handle
 \param value is scale delta
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceScaleDelta(unsigned int handle_id, float value);

/**
 \brief Set instance translate delta.
 \param handle_id is the target instance handle
 \param value is translate delta
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTranslateDelta(unsigned int handle_id, float value);

/**
 \brief Set instance target rotation angle.
 \param handle_id is the target instance handle
 \param value is target rotation angle
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTargetAngle(unsigned int handle_id, float value);

/**
 \brief Set instance target xyz position.
 \param handle_id is the target instance handle
 \param x is position of x world coordinate
 \param y is position of y world coordinate
 \param z is position of z world coordinate
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTargetPosition(unsigned int handle_id, float x,
                                           float y, float z);

/**
 \brief Set instance target rotation angle gradually.
 \param handle_id is the target instance handle
 \param value is target rotation angle
 \param frame_count is frame count
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTargetAngleGradually(unsigned int handle_id,
                                                 float value, int frame_count);

/**
 \brief Set instance target xyz position gradually.
 \param handle_id is the target instance handle
 \param x is position of x world coordinate
 \param y is position of y world coordinate
 \param z is position of z world coordinate
 \param frame_count is frame count
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTargetPositionGradually(unsigned int handle_id,
                                                    float x, float y, float z,
                                                    int frame_count);

/**
 \brief Enable instance rotation without animation translation.
 \param handle_id is the target instance handle
 \param enable > 0 rotate without animation translation
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceRotateWithoutAnimationTranslation(
    unsigned int handle_id, int enable);

/**
 \brief Set instance target xyz position range.
 \param handle_id is the target instance handle
 \param min_x is min position of x world coordinate
 \param min_y is min position of y world coordinate
 \param min_z is min position of z world coordinate
 \param max_x is max position of x world coordinate
 \param max_y is max position of y world coordinate
 \param max_z is max position of z world coordinate
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceTargetPositionRange(unsigned int handle_id,
                                                float min_x, float min_y,
                                                float min_z, float max_x,
                                                float max_y, float max_z);

/**
 \brief Set instance scale center and scale ratio.
 \param handle_id is the target instance handle
 \param x is scale center position of x
 \param y is scale center position of y
 \param z is scale center position of z
 \param scale is scale ratio
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceScale(unsigned int handle_id, float scale_center_x,
                                  float scale_center_y, float scale_center_z,
                                  float scale_ratio);

/**
 \brief Set instance color.
 \param handle_id is the target instance handle
 \param color_name is the color name
 \param r is color of R channel, from 0 to 255
 \param g is color of G channel, from 0 to 255
 \param b is color of B channel, from 0 to 255
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceColor(unsigned int handle_id,
                                  const char* color_name, int r, int g, int b);

/**
 \brief Set instance color intensity, for old color change type.
 \param handle_id is the target instance handle
 \param color_name is the color name
 \param intensity, intensity
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceColorIntensity(unsigned int handle_id,
                                           const char* color_name,
                                           float intensity);

/**
 \brief Set instance single face beauty color.
 \param handle_id is the target instance handle
 \param face_beauty_handle is the target face beauty item handle
 \param r is color of R channel, from 0 to 255
 \param g is color of G channel, from 0 to 255
 \param b is color of B channel, from 0 to 255
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceFacebeautyColor(unsigned int handle_id,
                                            int face_beauty_handle, int r,
                                            int g, int b);
/**
 \brief Enable instance self collision.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceSelfCollision(unsigned int handle_id,
                                             int enable);

/*
 * animation releated api
 */
/**
 \brief Play instance target animation.
 \param handle_id is the target instance handle
 \param anim_handle is target animation item handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPlayInstanceAnimation(unsigned int handle_id, int anim_handle);

/**
 \brief Play instance target animation once.
 \param handle_id is the target instance handle
 \param anim_handle is target animation item handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPlayInstanceAnimationOnce(unsigned int handle_id,
                                           int anim_handle);

/**
 \brief Start or continue to play instance current animation again.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuStartInstanceAnimation(unsigned int handle_id);

/**
 \brief Pause instance current animation.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuPauseInstanceAnimation(unsigned int handle_id);

/**
 \brief Stop instance current animation.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuStopInstanceAnimation(unsigned int handle_id);

/**
 \brief Restart instance current animation.
 \param handle_id is the target instance handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetInstanceAnimation(unsigned int handle_id);

/**
 \brief Set instance animation transition time.
 \param handle_id is the target instance handle
 \param time is transition time in seconds
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceAnimationTransitionTime(unsigned int handle_id,
                                                    float time);

/**
 \brief Turn on or off instance animation internal lerp.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceAnimationInternalLerp(unsigned int handle_id,
                                                     int enable);

/*
 * DynamicBone releated api
 */

/**
 \brief Enable DynamicBone or not.
 \param handle_id is the target scene handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableDynamicBone(unsigned int handle_id, int enable);

/**
 \brief Reset instance DynamicBone rigid body position.
 \param handle_id is the target instance handle
 \param immediate > 0 means reset DynamicBone immediate, <= 0 means delayed
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetInstanceDynamicBone(unsigned int handle_id,
                                          int immediate);

/**
 \brief Refresh/rebuild instance DynamicBone, time consuming
 \param handle_id is the target instance handle
 \param immediate > 0 means reset DynamicBone immediate, <= 0 means delayed
 \return zero for failed, one for success
*/
FUNAMA_API int fuRefreshInstanceDynamicBone(unsigned int handle_id,
                                            int immediate);
/**
 \brief Enable instance model mat to bone or not
 \param handle_id is the target instance handle
 \param enable > 0 means enable , enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceModelMatToBone(unsigned int handle_id,
                                              int enable);

/**
 \brief Open instance single mesh DynamicBone or close
 \param handle_id is the target instance handle
 \param mesh_handle is target mesh item handle
 \param enable > 0 means open, enable <= 0 means close
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceSingleDynamicBone(unsigned int handle_id,
                                                 int mesh_handle, int enable);

/**
 \brief Enable instance DynamicBone teleport mode or not.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceDynamicBoneTeleportMode(unsigned int handle_id,
                                                       int enable);

/**
 \brief Enable instance DynamicBone root translation speed limit mode or not.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceDynamicBoneRootTranslationSpeedLimitMode(
    unsigned int handle_id, int enable);

/**
 \brief Enable instance DynamicBone root rotation speed limit mode or not.
 \param handle_id is the target instance handle
 \param enable > 0 means turn on , enable <= 0 means turn off
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableInstanceDynamicBoneRootRotationSpeedLimitMode(
    unsigned int handle_id, int enable);

/*
 * MVP related api
 */

/**
 \brief Use orthogonal projection or perspective projection for the target
 scene.
 \param handle_id is the target scene handle
 \param enable = 1 means use orthogonal projection, enable = 0 means use
 perspective projection
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableOrthogonalProjection(unsigned int handle_id, int enable);

/**
 \brief Set perspective projection matrix's fov for the target scene.
 \param handle_id is the target scene handle
 \param fov is the degree of angle, from 0 to 180
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetProjectionMatrixFov(unsigned int handle_id, float fov);

/**
 \brief Set orthogonal projection matrix's frustum size for the target scene.
 \param handle_id is the target scene handle
 \param size is frustum size in X-coordinate
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetProjectionMatrixOrthoSize(unsigned int handle_id,
                                              float size);

/**
 \brief Set projection matrix's z_near for the target scene.
 \param handle_id is the target scene handle
 \param z_near
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetProjectionMatrixZnear(unsigned int handle_id, float z_near);

/**
 \brief Set projection matrix's z_far for the target scene.
 \param handle_id is the target scene handle
 \param z_far
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetProjectionMatrixZfar(unsigned int handle_id, float z_far);

/**
 \brief Set view matrix for the target scene.
 \param handle_id is the target scene handle
 \param eye_x
 \param eye_y
 \param eye_z
 \param center_x
 \param center_y
 \param center_z
 \param up_x
 \param up_y
 \param up_z
 \return zero for failed, one for success
*/

FUNAMA_API int fuSetViewMatrix(unsigned int handle_id, float eye_x, float eye_y,
                               float eye_z, float center_x, float center_y,
                               float center_z, float up_x, float up_y,
                               float up_z);

/**
 \brief Enable use outer MVP matrix for the target scene.
 \param handle_id is the target scene handle
 \param enable > 0 means use outer MVP matrix, enable <= 0 means not
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableOuterMVPMatrix(unsigned int handle_id, int enable);

/**
 \brief Set outer projection matrix for the target scene.
 \param handle_id is the target scene handle
 \param mat, 4x4 matrix
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetOuterProjectionMatrix(unsigned int handle_id,
                                          const float* mat);

/**
 \brief Set outer view matrix for the target scene.
 \param handle_id is the target scene handle
 \param mat, 4x4 column major matrix
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetOuterViewMatrix(unsigned int handle_id, const float* mat);

/**
 \brief Set background params for the target scene.
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param x_size is normalized width of background, from 0.0 to 1.0
 \param y_size is normalized height of background, from 0.0 to 1.0
 \param x_offset is normalized offset , form -1.0 to 1.0
 \param x_offset is normalized offset , form -1.0 to 1.0
 \param is_foreground, is foreground or background
 \param mode, 0 is for stretch, 1 is for crop
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetBackgroundParams(unsigned int handle_id, int bg_handle,
                                     float x_size, float y_size, float x_offset,
                                     float y_offset, int is_foreground,
                                     int mode);

/**
 \brief Set sprite usage, by default sprite is a normal 2d sprite
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param is_mask, if usage==1, it's a 2d mask, if usage==2, it's a sprite clipped
 by mask \return zero for failed, one for success
*/
FUNAMA_API int fuSetSpriteUsage(unsigned int handle_id, int bg_handle,
                                int usage);

/**
 \brief Update background texture with a rgba buffer
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param value rgba buffer
 \param width image width
 \param height image height
 \return zero for failure, non-zero for success
*/
FUNAMA_API int fuUpdateBackgroundTexture(unsigned int handle_id, int bg_handle,
                                         void* value, int width, int height);

/**
 \brief Set sprite9 params for the target scene.
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param src_offset_to_left_edge is the distance from source image left edge in
 pixel \param src_offset_to_right_edge is the distance from source image right
 edge in pixel \param src_offset_to_top_edge is the distance from source image
 top edge in pixel \param src_offset_to_bottom_edge is the distance from source
 image bottom edge in pixel \param x_size is normalized width of background,
 from 0.0 to 1.0 \param y_size is normalized height of background, from 0.0
 to 1.0 \param x_offset is normalized offset , form -1.0 to 1.0 \param x_offset
 is normalized offset , form -1.0 to 1.0 \param is_foreground, is foreground or
 background \return zero for failed, one for success
*/
FUNAMA_API int fuSetSprite9Params(unsigned int handle_id, int bg_handle,
                                  int src_offset_to_left_edge,
                                  int src_offset_to_right_edge,
                                  int src_offset_to_top_edge,
                                  int src_offset_to_bottom_edge, float x_size,
                                  float y_size, float x_offset, float y_offset,
                                  int is_foreground);

/**
 \brief Update sprite9 texture with a rgba buffer
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param value rgba buffer
 \param width image width
 \param height image height
 \return zero for failure, non-zero for success
*/
FUNAMA_API int fuUpdateSprite9Texture(unsigned int handle_id, int bg_handle,
                                      void* value, int width, int height);

/**
 \brief Reset 2D background or foreground animation for the target scene.
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetBackgroundAnimation(unsigned int handle_id,
                                          int bg_handle);

/**
 \brief Enable 2D background or foreground animation Loop.
 \param handle_id is the target scene handle
 \param bg_handle is the target background item handle
 \param enable is enable loop
 \return zero for failed, one for success
*/
FUNAMA_API int fuEnableBackgroundAnimationLoop(unsigned int handle_id,
                                               int bg_handle, int enable);

/**
 \brief Reset light animation for the target scene.
 \param handle_id is the target scene handle
 \return zero for failed, one for success
*/
FUNAMA_API int fuResetLightAnimation(unsigned int handle_id);

/**
 \brief Set outer model matrix for the target scene.
 \param handle_id is the target scene handle
 \param mat, 4x4 column major matrix
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetOuterModelMatrix(unsigned int handle_id, const float* mat);

/*
 * get api
 */

/**
 \brief Get projection matrix's z_near for the target scene.
 \param handle_id is the target scene handle
 \return z_near
*/
FUNAMA_API float fuGetProjectionMatrixZnear(unsigned int handle_id);

/**
 \brief Get projection matrix's z_far for the target scene.
 \param handle_id is the target scene handle
 \return z_far
*/
FUNAMA_API int fuGetProjectionMatrixZfar(unsigned int handle_id);

/**
 \brief Get camera animation frame number for the target scene.
 \param handle_id is the target scene handle
 \param anim_handle is the target camera animation item handle
 \return frame number
*/
FUNAMA_API int fuGetCameraAnimationFrameNumber(unsigned int handle_id,
                                               int anim_handle);

/**
 \brief Get camera animation progress for the target scene.
 \param handle_id is the target scene handle
 \param anim_handle is the target camera animation item handle
 \return progress
*/
FUNAMA_API float fuGetCameraAnimationProgress(unsigned int handle_id,
                                              int anim_handle);

/**
 \brief Get camera animation transition progress for the target scene.
 \param handle_id is the target scene handle
 \return transition progress
*/
FUNAMA_API float fuGetCameraAnimationTransitionProgress(unsigned int handle_id);

/**
 \brief Get instance facepup original value.
 \param handle_id is the target instance handle
 \param name is the parameter name
 \return facepup original value
*/
FUNAMA_API float fuGetInstanceFacepupOriginalValue(unsigned int handle_id,
                                                   const char* name);

/**
 \brief Get instance facepup array.
 \param handle_id is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
*/
FUNAMA_API int fuGetInstanceFacepupArray(unsigned int handle_id, float* ret,
                                         int size);

/**
 \brief Get instance skin color index.
 \param handle_id is the target instance handle
 \return skin color index
 */
FUNAMA_API int fuGetInstanceSkinColorIndex(unsigned int handle_id);

/**
 \brief Get instance local boundingbox, six dimensional
 \param handle_id is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceLocalBoundingBox(unsigned int handle_id, float* ret,
                                             int size);

/**
 \brief Get instance position, three dimensional
 \param handle_id is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstancePosition(unsigned int handle_id, float* ret,
                                     int size);

/**
 \brief Get instance head center screen coordinate, two dimensional
 \param handle_id is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceHeadCenterScreenCoordinate(unsigned int handle_id,
                                                       float* ret, int size);

/**
 \brief Get instance bone screen coordinate, two dimensional
 \param handle_id is the target instance handle
 \param name is the target bone name
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceBoneScreenCoordinate(unsigned int handle_id,
                                                 const char* name, float* ret,
                                                 int size);

/**
 \brief Get instance Face vertex screen coordinate, two dimensional
 \param handle_id is the target instance handle
 \param index is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceFaceVertexScreenCoordinate(unsigned int handle_id,
                                                       int index, float* ret,
                                                       int size);

/**
 \brief Get instance boundingBox screen coordinate, four dimensional
 \param handle_id is the target instance handle
 \param ret allocated memory space as container
 \param size is number of float allocated in ret
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceBoundingBoxScreenCoordinate(unsigned int handle_id,
                                                        float* ret, int size);

/**
 \brief Get instance boundingBox screen coordinate, four dimensional, with aabb
 offset 
 \param handle_id is the target instance handle 
 \param ret allocated memory space as container 
 \param size is number of float allocated in ret
 \param x_min_offset is offset of local aabb min x
 \param y_min_offset is offset of local aabb min y
 \param z_min_offset is offset of local aabb min z
 \param x_max_offset is offset of local aabb max x
 \param y_max_offset is offset of local aabb max y
 \param z_max_offset is offset of local aabb max z
 \return 1 means successful fetch, container filled with info 0 means failure
 */
FUNAMA_API int fuGetInstanceBoundingBoxScreenCoordinateWithOffset(
    unsigned int handle_id, float* ret, int size, float x_min_offset,
    float y_min_offset, float z_min_offset, float x_max_offset,
    float y_max_offset, float z_max_offset);

/**
 \brief Get instance target animation frame number.
 \param handle_id is the target instance handle
 \param anim_handle is target animation item handle
 \return animation frame number
 */
FUNAMA_API int fuGetInstanceAnimationFrameNumber(unsigned int handle_id,
                                                 int anim_handle);

/**
 \brief Get instance target animation progress
 \param handle_id is the target instance handle
 \param anim_handle is target animation item handle
 \return animation progress
 */
FUNAMA_API float fuGetInstanceAnimationProgress(unsigned int handle_id,
                                                int anim_handle);

/**
 \brief Get instance target animation transition progress
 \param handle_id is the target instance handle
 \param anim_handle is target animation item handle
 \return animation transition progress
 */
FUNAMA_API float fuGetInstanceAnimationTransitionProgress(
    unsigned int handle_id, int anim_handle);

/**
 \brief Set the human processor type.
 \param handle_id: the target instance handle
 \param human_processor_type: 0 for AI fuai, 1 for the rigging_bvhinput_processor.
 \return zero for failed, one for success
*/
FUNAMA_API int fuSetInstanceHumanProcessorType(unsigned int handle_id,
                                               int human_processor_type);

/**
 \brief Set the rigging retargeter follow mode.
 \param handle_id is the target instance handle
 \param follow_mode: follow_mode, only support
    FUAIHUMAN_FOLLOW_MODE_FIX: fix the root at it's bind position.
    FUAIHUMAN_FOLLOW_MODE_ALIGN: align the avatar to the real
 person, but scale the root translation by the avatar leg height(root to
 ground).
    FUAIHUMAN_FOLLOW_MODE_STAGE: make the avatar move from the origin(foot
 from the origin).
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterAvatarFollowMode(
    unsigned int handle_id, FUAIHUMANFOLLOWMODE follow_mode);

/**
 \brief Set the rigging retargeter translation scale under FUAIHUMAN_FOLLOW_MODE_FIX mode.
 \param handle_id is the target instance handle
 \param scale_x: scale of root's x. >= 0
 \param scale_y: scale of root's y. >= 0
 \param scale_z: scale of root's z. >= 0
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterAvatarFixModeTransScale(
    unsigned int handle_id, float scale_x, float scale_y, float scale_z);

/**
 \brief Set the rigging retargeter target bonemap.
 \param handle_id is the target instance handle
 \param bonemap_buffer_ptr: json file description of skeleton hierarchy. ref to boneMap.json
 \param bonemap_buffer_size, size of data in bytes.
 \param bonemap_hashcode, bonemap's hashcode.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterAvatarBonemap(
    unsigned int handle_id, const char* bonemap_buffer_ptr,
    const int bonemap_buffer_size, const unsigned long long bonemap_hashcode);

/**
 \brief Set the rigging retargeter retarget mapping.
 \param handle_id is the target instance handle
 \param mapping_buffer_ptr: json file description of the retarget mapping.
 \param mapping_buffer_size, size of data in bytes.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterRetargetMapping(
    unsigned int handle_id, const char* mapping_buffer_ptr,
    const int mapping_buffer_size);

/**
 \brief Set the rigging retargeter use collision or not.
 \param handle_id is the target instance handle
 \param use_collision: use collision or not.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterUseCollision(
    unsigned int handle_id, bool use_collision);

/**
 \brief Set the rigging retargeter retarget collision config.
 \param handle_id is the target instance handle
 \param collision_config_ptr: json file description of the collision config.
 \param collision_config_size, size of data in bytes.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterCollisionConfig(
    unsigned int handle_id, const char* collision_config_ptr,
    const int collision_config_size);

/**
 \brief Set the rigging retargeter use euler limits or not.
 \param handle_id is the target instance handle
 \param use_euler_limits: use euler limits or not.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterUseEulerLimits(
    unsigned int handle_id, bool use_euler_limits);

/**
 \brief Set the rigging retargeter retarget euler limit config.
 \param handle_id is the target instance handle
 \param euler_limit_config_ptr: json file description of the euler limit config.
 \param euler_limit_config_size, size of data in bytes.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterEulerLimitConfig(
    unsigned int handle_id, const char* euler_limit_config_ptr,
    const int euler_limit_config_size);

/**
 \brief Set the rigging retargeter retarget final mirror type.
 \param handle_id is the target instance handle
 \param final_mirror_type: final mirror type. Default FUAIHUMAN_MIRROR_NONE(3).
                           0:left-right mirror
                           1:top-bottom mirror
                           2:both mirror(rotate 180 degree)
                           3:no mirror.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuSetInstanceRiggingRetargeterFinalMirrorType(
    unsigned int handle_id, FUAIHUMANMIRRORTYPE final_mirror_type);


/**
 \brief Set the rigging bvh input processor config.
 \param handle_id is the target scene handle
 \param bvh_buffer_ptr: bvh header buffer ptr.
 \param bvh_buffer_size, bvh header buffer length.
 \param mapping_buffer_ptr: json file description of the retarget mapping.
 \param mapping_buffer_size, size of data in bytes.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuRiggingBVHInputProcessorSetConfig(
    unsigned int handle_id, const char* bvh_buffer_ptr,
    const int bvh_buffer_size, const char* mapping_buffer_ptr,
    const int mapping_buffer_size);

/**
 \brief Feed the rigging bvh input processor with one motion frame.
 \param handle_id is the target scene handle
 \param motion_frame_ptr: pointer to motion frame data(structure is defined by bvh header setted by fuRiggingBVHInputProcessorSetConfig).
 \param motion_frame_len: length of the motion frame data.
 \return zero for failed, one for scuess
 */
FUNAMA_API int fuRiggingBVHInputProcessorFeedMotionFrame(
    unsigned int handle_id, const float* motion_frame_ptr,
    const int motion_frame_len);


#ifdef __cplusplus
}
#endif

#endif  // !CNAMASDK_H
