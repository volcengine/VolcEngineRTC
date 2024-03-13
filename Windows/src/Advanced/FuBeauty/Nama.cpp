#include <map>
#include <QCoreApplication>
#include "Nama.h"
#include "FConfig.h"	

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "Language.h"

#include "authpack.h"


#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <strmif.h>
#include <control.h>
#else
#include <OpenGL/OpenGL.h>

#endif
#include <string>
#include <thread>
#include <QDir>

#include <QDebug>

#pragma comment(lib, "strmiids.lib")

#ifdef CNAMASDK_H

#define MAX_BEAUTYFACEPARAMTER 5
#define MAX_FACESHAPEPARAMTER 9

using namespace NamaNameSpace;

int Nama::renderBundleCategory = -1;
std::map<int, std::vector<std::string>> categoryBundles;//bundle category目录下所有的bundle


int Nama::m_curFilterIdx;
int Nama::m_curRenderItem = -1;
int Nama::m_curBindedItem = -1;
int Nama::mEnableSkinDect = 1; //精准美肤
int Nama::mEnableHeayBlur = 0;
float Nama::mFaceBeautyLevel[5] = { 0.0f };
float Nama::mFaceShapeLevel[9] = { 0.0f };
float Nama::mFilterLevel[10] = { 100,100,100,100,100, 100,100,100,100,100 };

std::string Nama::initFuError;
std::string Nama::bundleInfo;
std::string Nama::filterInfo;
std::string g_fuDataDir;

#ifdef _WIN32
static HGLRC new_context;


HDC hgldc = nullptr;
HGLRC hglrc = nullptr;
PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),
    1u,
    PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW,
    PFD_TYPE_RGBA,
    32u,
    0u, 0u, 0u, 0u, 0u, 0u,
    8u,
    0u,
    0u,
    0u, 0u, 0u, 0u,
    24u,
    8u,
    0u,
    PFD_MAIN_PLANE,
    0u,
    0u, 0u };
#else
CGLContextObj cglContext = nullptr;
#endif


std::string Nama::mFilters[6] = { "origin", "bailiang1", "fennen1", "xiaoqingxin1", "lengsediao1", "nuansediao1" };

std::map<int, int> modules = { {Animoji,16},{ItemSticker,2},{ARMask,32},{ChangeFace,128},
{ExpressionRecognition,2048},{MusicFilter,131072},{BackgroundSegmentation,256},
{GestureRecognition,512},{MagicMirror,65536},{PortraitDrive,32768},{Makeup,524288},
{Hair,524288},{ChangeFaceEx,8388608},{ExpressionGif,16777216}, {Facebeauty,1} ,{LightMakeup,0} ,{Facepup,0} };

std::map<int, int> modules1 = { {Animoji,0},{ItemSticker,0},{ARMask,0},{ChangeFace,0},
{ExpressionRecognition,0},{MusicFilter,0},{BackgroundSegmentation,0},
{GestureRecognition,0},{MagicMirror,0},{PortraitDrive,0},{Makeup,0},
{Hair,0},{ChangeFaceEx,0},{ExpressionGif,0}, {Facebeauty,0} ,{LightMakeup,8} ,{Facepup,16} };

std::string Nama::gBundlePath[BUNDLE_COUNT_IN_USE] = {
 "/items/Animoji/",
 "/items/ItemSticker/",
 "/items/ARMask/",
 "/items/ChangeFace/",
 "/items/ExpressionRecognition/",
 "/items/MusicFilter/",
 "/items/BackgroundSegmentation/",
 "/items/GestureRecognition/",
 "/items/MagicMirror/",
 "/items/PortraitDrive/",
 "/items/Makeup/"
};





Nama::Nama()
{
    mFrameID = 0;
    mMaxFace = 1;
    mIsBeautyOn = true;
    mBeautyHandles = 0;
    mMakeUpHandle = 0;
    mNewFaceTracker = -1;
    g_fuDataDir = QCoreApplication::applicationDirPath().toStdString() + "/Resources/faceunity/assets";
    Nama::resetBeautyParam();//beautyFace
    Nama::resetShapeParam();//faceshape
    Nama::loadAllBundles();
    m_namaInited = false;
    m_loadBundles = true;
}

Nama::~Nama()
{
    if (m_namaInited) {
        fuDestroyAllItems();//Note: Do not use an items are destroyed
        fuOnDeviceLost();//Note:  destroy OpenGL resources nama created
        fuDestroyLibData();//Note: destory thread resources nama created
    }
}

void Nama::resetBeautyParam()
{
    mFaceBeautyLevel[0] = 0;
    mFaceBeautyLevel[1] = 0;
    mFaceBeautyLevel[2] = 0;
    mFaceBeautyLevel[3] = 0;
    mFaceBeautyLevel[4] = 0;
}

void Nama::resetShapeParam()
{
    mFaceShapeLevel[0] = 0;
    mFaceShapeLevel[1] = 0;
    mFaceShapeLevel[2] = 0;
    mFaceShapeLevel[3] = 0;
    mFaceShapeLevel[4] = 0;
    mFaceShapeLevel[5] = 0;

    mFaceShapeLevel[6] = 0;
    mFaceShapeLevel[7] = 0;
    mFaceShapeLevel[8] = 0;
}

void Nama::loadAllBundles()
{
    for (int i = 0; i < BUNDLE_COUNT_IN_USE; i++) {
        std::vector<std::string> vec_bundles;
        Nama::FindAllBundle(g_fuDataDir + gBundlePath[i], vec_bundles);
        categoryBundles[i] = vec_bundles;
    }
}

bool InitOpenGL()
{
#ifdef _WIN32
    HWND hw = CreateWindowExA(
        0, "EDIT", "", ES_READONLY,
        0, 0, 1, 1,
        NULL, NULL,
        GetModuleHandleA(NULL), NULL);
    hgldc = GetDC(hw);
    int spf = ChoosePixelFormat(hgldc, &pfd);
    if (spf == 0) {
        return false;
    }
    int ret = SetPixelFormat(hgldc, spf, &pfd);
    if (!ret) {
        return false;
    }
    hglrc = wglCreateContext(hgldc);
    //BOOL retgl = wglMakeCurrent(hgldc, hglrc);

#else
    CGLPixelFormatAttribute attrib[13] = {
        kCGLPFAOpenGLProfile,
        (CGLPixelFormatAttribute)kCGLOGLPVersion_Legacy,
        kCGLPFAAccelerated,
        kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
        kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
        kCGLPFADoubleBuffer,
        kCGLPFASampleBuffers, (CGLPixelFormatAttribute)1,
        kCGLPFASamples, (CGLPixelFormatAttribute)4,
        (CGLPixelFormatAttribute)0
    };
    CGLPixelFormatObj pixelFormat = NULL;
    GLint numPixelFormats = 0;
    CGLChoosePixelFormat(attrib, &pixelFormat, &numPixelFormats);
    CGLError err = CGLCreateContext(pixelFormat, NULL, &cglContext);
    if (err) {
        return false;
    }
#endif

    return true;
}

bool Nama::InitNama()
{
    if (m_namaInited) {
        return true;
    }

    if (g_auth_package == NULL) {
        qWarning() << Q_FUNC_INFO << "auth package error";
        return false;
    }
    int ret = fuSetup(nullptr, 0, nullptr, g_auth_package, sizeof(g_auth_package));
    if (ret == 0) {
        qWarning() << Q_FUNC_INFO << "fusetup error";
        return false;
    }

    if (!InitOpenGL()) {
        qWarning() << Q_FUNC_INFO << "initOpenGL failed";
        return false;
    }
    m_namaInited = true;
    qDebug() << Q_FUNC_INFO << "init succeed";
    return true;
}

bool NamaNameSpace::Nama::checkBundles()
{
    if (m_loadBundles) {
        loadBundles();
        m_loadBundles = false;
    }
    updateBundles();

    return true;
}

bool NamaNameSpace::Nama::loadBundles()
{
    fuDestroyAllItems();

    std::vector<char> ai_model_data;
    if (false == LoadBundle(g_fuDataDir + g_ai_faceprocessor, ai_model_data))
    {

        initFuError += g_fuDataDir + g_ai_faceprocessor;
        //return false;
    }
    fuLoadAIModelFromPackage(reinterpret_cast<float*>(&ai_model_data[0]), ai_model_data.size(), FUAITYPE::FUAITYPE_FACEPROCESSOR);

    std::vector<char> fxaa_data;
    if (false == LoadBundle(g_fuDataDir + g_fxaa, fxaa_data))
    {
        initFuError += g_fuDataDir + g_fxaa;
        return false;
    }
    mFxaaHandles = fuCreateItemFromPackage(fxaa_data.data(), fxaa_data.size());
    //fuSetExpressionCalibration(1);

    mModuleCode = fuGetModuleCode(0);
    mModuleCode1 = fuGetModuleCode(1);
    //read beauty data and set beauty parameters
    if (CheckModuleCode(Facebeauty)) {
        std::vector<char> propData;
        if (false == LoadBundle(g_fuDataDir + g_faceBeautification, propData))
        {
            initFuError = "load face beautification data failed.";
            return false;
        }
        std::cout << "load face beautification data." << std::endl;

        mBeautyHandles = fuCreateItemFromPackage(&propData[0], propData.size());
    }

    //read makeup data
    if (CheckModuleCode(Makeup)) {
        std::vector<char> propData;
        if (false == LoadBundle(g_fuDataDir + g_Makeup, propData))
        {
            initFuError = "load face makeup data failed.";
            return false;
        }
        std::cout << "load face makeup data." << std::endl;

        mMakeUpHandle = fuCreateItemFromPackage(&propData[0], propData.size());

    }
    if (fuGetSystemError())
    {
        initFuError = fuGetSystemErrorString(fuGetSystemError());
        return false;
    }
    initFuError = "";
    //fuSetDefaultOrientation(0);
    float fValue = 0.5f;
    fuSetFaceTrackParam((void*)"mouth_expression_more_flexible", &fValue);
    return false;
}

bool NamaNameSpace::Nama::updateBundles()
{
    if (m_needUpdateBeauty) {
        UpdateBeauty();
        m_needUpdateBeauty = false;
    }

    if (m_needUpdateFilter) {
        UpdateFilter(m_curFilterIdx);
        UpdateBeauty();
        m_needUpdateFilter = false;
    }
    if (m_needUpdateBundle) {
        std::string full_path = getBundleFullPath(m_bundleType1, m_bundleType2);
        if (!SelectBundle(full_path)) {//select bundle failed
            qWarning() << Q_FUNC_INFO << "select bundle failed" << m_bundleType1 << m_bundleType2;
        }
        m_needUpdateBundle = false;
    }
    return false;
}

void NamaNameSpace::Nama::setARBundles(int type1, int type2) {
    m_bundleType1 = type1;
    m_bundleType2 = type2;
}

int NamaNameSpace::Nama::processVideoFrame(uchar* frame, int width, int height)
{
    if (!m_namaInited) return -1;
    do {

        //make env
        makeCurrent();

        //bundles
        checkBundles();

        //renderer
        RenderItems(frame, width, height, 13);

        //done env
        doneCurrent();
    } while (false);

    return 0;
}

void NamaNameSpace::Nama::makeCurrent()
{
#ifdef _WIN32
    
    wglMakeCurrent(hgldc, hglrc);
#else
    CGLSetCurrentContext(cglContext);
#endif
}

void NamaNameSpace::Nama::doneCurrent()
{
#ifdef _WIN32
    wglMakeCurrent(hgldc, nullptr);
#else
    CGLSetCurrentContext(nullptr);
#endif
}

const std::string NamaNameSpace::Nama::getBundleFullPath(int type1, int type2)
{
    if (categoryBundles.count(type1) == 0) {
        qWarning() << Q_FUNC_INFO << "type1 error:" << type1;
        return "";
    }
    if (categoryBundles[type1].size() <= type2) {
        qWarning() << Q_FUNC_INFO << "type2 error:" << type2;
        return "";
    }
    std::string itemName = categoryBundles[type1][type2];
    std::string result = g_fuDataDir + Nama::gBundlePath[type1] + itemName;
    return result;
}


void Nama::UpdateFilter(int index)
{
    if (false == mIsBeautyOn || mBeautyHandles == 0)return;

    fuItemSetParams(mBeautyHandles, "filter_name", &mFilters[index][0]);
}

void Nama::UpdateBeauty()
{
    if (mBeautyHandles == 0)
    {
        return;
    }
    if (false == mIsBeautyOn)return;

    for (int i = 0; i < MAX_BEAUTYFACEPARAMTER; i++)
    {
        if (i == 0)//Blur
        {
            fuItemSetParamd(mBeautyHandles, const_cast<char*>(faceBeautyParamName[i].c_str()), Nama::mFaceBeautyLevel[i] * 6.0 / 100.f);
        }
        else
        {
            fuItemSetParamd(mBeautyHandles, const_cast<char*>(faceBeautyParamName[i].c_str()), Nama::mFaceBeautyLevel[i] / 100.f);
        }
    }
    std::string faceShapeParamName[] = { "cheek_thinning","eye_enlarging", "intensity_chin", "intensity_forehead", "intensity_nose","intensity_mouth",
     "cheek_v","cheek_narrow","cheek_small" };
    for (int i = 0; i < MAX_FACESHAPEPARAMTER; i++)
    {
        if (i == 2 || i == 3 || i == 5)
        {
            Nama::mFaceShapeLevel[i] += 50;
        }
        fuItemSetParamd(mBeautyHandles, const_cast<char*>(faceShapeParamName[i].c_str()), Nama::mFaceShapeLevel[i] / 100.0f);
        if (i == 2 || i == 3 || i == 5)
        {
            Nama::mFaceShapeLevel[i] -= 50;
        }
    }
    fuItemSetParamd(mBeautyHandles, "skin_detect", Nama::mEnableSkinDect);
    std::map<int, int> blurType = { {0,2},{1,0},{2,1} };
    fuItemSetParamd(mBeautyHandles, "blur_type", blurType[Nama::mEnableHeayBlur]);
    fuItemSetParamd(mBeautyHandles, "face_shape_level", 1);
    fuItemSetParamd(mBeautyHandles, "filter_level", Nama::mFilterLevel[Nama::m_curFilterIdx] / 100.0f);
}

bool Nama::SelectBundle(std::string bundleName)
{
    qDebug() << Q_FUNC_INFO << "select:" << bundleName.c_str() << ",type1:" << m_bundleType1 << m_bundleType2;
    if (bundleName.empty()) return false;
    int bundleID = -1;
    //if not load bundle, then load
    if (0 == mBundlesMap[bundleName])
    {
        //certificate doesn't have authority to read this bundle
        if (!CheckModuleCode(m_bundleType1))
        {
            return false;
        }
        std::vector<char> propData;
        if (false == LoadBundle(bundleName, propData))
        {
            bundleInfo = "load prop data failed.";
            //std::cout << "load prop data failed." << std::endl;
            Nama::m_curRenderItem = -1;
            return false;
        }
        std::cout << "load prop data." << std::endl;
        //max Map size
        if (mBundlesMap.size() > MAX_NAMA_BUNDLE_NUM)
        {
            fuDestroyItem(mBundlesMap.begin()->second);
            mBundlesMap.erase(mBundlesMap.begin());
            printf("cur map size : %d \n", mBundlesMap.size());
        }

        bundleID = fuCreateItemFromPackage(&propData[0], propData.size());
        mBundlesMap[bundleName] = bundleID;
        //Bind makeup
        if (Nama::m_bundleType1 == BundleCategory::Makeup)
        {
            if (Nama::m_curBindedItem != -1)
            {
                fuUnbindItems(mMakeUpHandle, &Nama::m_curBindedItem, 1);
            }
            fuBindItems(mMakeUpHandle, &bundleID, 1);
            Nama::m_curBindedItem = bundleID;
        }
        else
        {
            //fuItemSetParamd(mMakeUpHandle, "is_makeup_on", 0);
        }
    }
    else
    {
        bundleID = mBundlesMap[bundleName];
        //bind makeup
        if (Nama::m_bundleType1 == BundleCategory::Makeup)
        {
            if (Nama::m_curBindedItem != -1)
            {
                fuUnbindItems(mMakeUpHandle, &Nama::m_curBindedItem, 1);
            }
            fuBindItems(mMakeUpHandle, &bundleID, 1);
            Nama::m_curBindedItem = bundleID;
        }
        else
        {
            //fuItemSetParamd(mMakeUpHandle, "is_makeup_on", 0);
        }
    }

    if (Nama::m_curRenderItem == bundleID)
    {
        //ubbind makeup data
        if (Nama::m_bundleType1 == BundleCategory::Makeup)
        {
            fuUnbindItems(mMakeUpHandle, &Nama::m_curRenderItem, 1);
            Nama::m_curBindedItem = -1;
        }
        Nama::m_curRenderItem = -1;
    }
    else
    {
        Nama::m_curRenderItem = bundleID;
        Nama::renderBundleCategory = Nama::m_bundleType1;
    }
    if (Nama::m_bundleType1 == PortraitDrive || Nama::m_bundleType1 == Animoji)
    {
        mMaxFace = 1;
    }
    else
    {
        mMaxFace = 4;
    }

    if (Nama::renderBundleCategory == Animoji)
    {
        fuItemSetParamd(Nama::m_curRenderItem, "{\"thing\":\"<global>\",\"param\":\"follow\"} ", 1);
    }
    else
    {
        int ret = fuItemSetParamd(Nama::m_curRenderItem, "{\"thing\":\"<global>\",\"param\":\"follow\"} ", 1);
        std::cout << ret << std::endl;
        int ret2 = fuGetSystemError();
        std::string s2 = fuGetSystemErrorString(ret2);
        s2 = fuGetSystemErrorString(ret);
    }
    bundleInfo = "";
    return true;
}

bool Nama::CheckModuleCode(int category)
{	
	return (mModuleCode & modules[category])  || (mModuleCode1 & modules1[category]);
}

int Nama::RenderItems(uchar* frame, int width, int height, int inframeType)
{
    if (frame == nullptr) return -100;
    int ret = 0;
    
    if (true)
    {
        
        fuSetMaxFaces(mMaxFace);
        {
            if (mNewFaceTracker != -1)
            {
                fuDestroyItem(mNewFaceTracker);
                mNewFaceTracker = -1;
            }
            int handle[] = { mBeautyHandles, Nama::m_curRenderItem };
            int handleSize = sizeof(handle) / sizeof(handle[0]);
            try {
               
                ret = fuRenderItemsEx2(FU_FORMAT_I420_BUFFER, reinterpret_cast<int*>(frame), FU_FORMAT_I420_BUFFER, reinterpret_cast<int*>(frame),
                    width, height, mFrameID, handle, handleSize, NAMA_RENDER_FEATURE_FULL, NULL);
            }
            catch (...) {
                
            }
        }

        if (fuGetSystemError())
        {
            std::string str_error = fuGetSystemErrorString(fuGetSystemError());
            qDebug() << Q_FUNC_INFO << "error:" << QString::fromStdString(str_error);
        }
        ++mFrameID;
    }
    return ret;
}

//LoadBundle
void Nama::FindAllBundle(std::string folder, std::vector<std::string> &files)
{
    IteratorFolder(folder.c_str(), files);
}

void Nama::IteratorFolder(const char* lpPath, std::vector<std::string> &fileList)
{
    if (lpPath == nullptr) return;
    std::string str_dir(lpPath);
    QDir dir(QString::fromStdString(str_dir));
    if (dir.exists()) {
        QStringList nameFilters;
        nameFilters << "*.bundle";
        QFileInfoList list = dir.entryInfoList(nameFilters, QDir::Files);

        foreach(const QFileInfo & fileInfo, list)
        {
            std::string text = fileInfo.fileName().toStdString();
            fileList.push_back(text);
        }
    }
}

namespace NamaNameSpace {

    size_t FileSize(std::ifstream& file)
    {
        std::streampos oldPos = file.tellg();
        file.seekg(0, std::ios::beg);
        std::streampos beg = file.tellg();
        file.seekg(0, std::ios::end);
        std::streampos end = file.tellg();
        file.seekg(oldPos, std::ios::beg);
        return static_cast<size_t>(end - beg);
    }

    bool LoadBundle(const std::string& filepath, std::vector<char>& data)
    {
        std::ifstream fin(filepath, std::ios::binary);
        if (false == fin.good())
        {
            fin.close();
            return false;
        }
        size_t size = FileSize(fin);
        if (0 == size)
        {
            fin.close();
            return false;
        }
        data.resize(size);
        fin.read(reinterpret_cast<char*>(&data[0]), size);

        fin.close();
        return true;
    }
}

#endif
