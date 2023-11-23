#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>

#if __has_include("CNamaSDK.h")
#include "CNamaSDK.h"
#endif


#ifdef CNAMASDK_H
class CCameraDS;
typedef unsigned char uchar;
#define BUNDLE_COUNT_IN_USE 11
#define WM_FU_MSGID(code) (WM_USER+0x1000+code)
#define EID_FU_INIT_ERROR         0x00000001
#define EID_FU_BUNDLE_ERROR       0x00000002
namespace NamaNameSpace   
{
    enum BundleItemSticker {
        ItemSticker_CatSparks,
        ItemSticker_newy1,
        ItemSticker_redribbt,
        ItemSticker_sdlr,
        ItemSticker_xlong_zh_fu,
        ItemSticker_Count,
    };
    enum BundleMaskType {
        MASK_baozi,
        MASK_bluebird,
        MASK_fenhudie,
        MASK_lanhudie,
        MASK_tiger,
        MASK_tiger_bai,
        MASK_tiger_huang,
        MASK_xiongmao,
        MASK_Count
    };
    enum BundleCategory
    {
        Animoji,
        ItemSticker,
        ARMask,
        ChangeFace,//not used now
        ExpressionRecognition,
        MusicFilter,
        BackgroundSegmentation,
        GestureRecognition,
        MagicMirror,
        PortraitDrive,
        Makeup,
        Hair,
        ChangeFaceEx,
        ExpressionGif,
        Facebeauty,
        LightMakeup,
        Facepup,

        Count
    };

    class Nama
    {
    public:
        static int renderBundleCategory;
        static int faceType;

        static int m_curFilterIdx;
        static int m_curRenderItem;
        static int m_curBindedItem; ;
       // static ImGuiID m_curRenderItemUIID;

        static int mEnableSkinDect;
        static int mEnableHeayBlur;
        static float mFaceBeautyLevel[5];
        static float mFaceShapeLevel[9];
        static float mFilterLevel[10];

        static std::string gBundlePath[BUNDLE_COUNT_IN_USE];

        static void resetBeautyParam();
        static void resetShapeParam();
        static void loadAllBundles();

        static void IteratorFolder(const char* lpPath, std::vector<std::string> &fileList);
        static void FindAllBundle(std::string folder, std::vector<std::string> &files);

        static std::string initFuError;
        static std::string bundleInfo;
        static std::string filterInfo;


        Nama();
        ~Nama();
        bool InitNama();
        bool checkBundles();
        bool loadBundles();
        bool updateBundles();
        int processVideoFrame(uchar* frame, int width, int height);
        void makeCurrent();
        void doneCurrent();
        const std::string getBundleFullPath(int type1, int type2);

        bool IsInited() { return mHasSetup; }
        bool SelectBundle(std::string bundleName);
        bool CheckModuleCode(int category);
        void UpdateFilter(int);
        void UpdateBeauty();
        int RenderItems(uchar* frame, int width, int height, int inframeType);
        void setARBundles(int type1, int type2);

    private:
        int mBeautyHandles;
        int mMakeUpHandle;
        int mNewFaceTracker;
        int mFxaaHandles;
        static bool mHasSetup;
        bool m_namaInited;
        bool m_loadBundles;
        

    public:
        bool m_needUpdateBeauty = false;//beautyskin and faceshape
        bool m_needUpdateFilter = false;//filter
        bool m_needUpdateBundle = false;
        int  m_bundleType1, m_bundleType2; //AR 
        
    public:
        int mIsBeautyOn;
        int mMaxFace;
        int mFrameID;
        int mModuleCode, mModuleCode1;
        static std::string mFilters[6];
        std::unordered_map<std::string, int> mBundlesMap;
    };

    size_t FileSize(std::ifstream& file);

    bool LoadBundle(const std::string& filepath, std::vector<char>& data);

}

template < class T>
std::string ConvertToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
#endif
