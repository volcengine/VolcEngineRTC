#ifndef CNAMASDK_TIMEPROFILE_H
#define CNAMASDK_TIMEPROFILE_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#ifdef NAMA_BUILD_SHARED_LIB
#define FUNAMA_API __declspec(dllexport)
#else
#define FUNAMA_API
#endif
#else
#define FUNAMA_API __attribute__((visibility("default")))
#endif

/**
 \brief Set Frame time profile
 \param enable - is enbale.
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetEnbale(bool enable);
/**
 \brief Set Frame time auto report interval
 \param interval - default is 300.
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetReportInterval(int interval);

/**
 \brief Set Frame time report detail
 \param enable, report detail
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetReportDetail(bool enable);

/**
 \brief Set Frame time auto report to console
 \param enable - is enbale.
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetAutoReportToConsole(bool enable);

/**
 \brief Set Frame time auto report to file
 \param enable - is enbale.
 \param file - file path.
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetAutoReportToFile(bool enable,
                                                      const char* file);

/**
 \brief Set Frame time auto report to server
 \param enable - is enbale.
 \param server_addr - remote server ip addr.
 \param port - port.
 \return void.
*/
FUNAMA_API void fuFrameTimeProfileSetAutoReportToServer(bool enable,
                                                        const char* server_addr,
                                                        int port);
/**
 \brief Start time profile root node
 \param lable - lable name.
 \return void.
*/
FUNAMA_API void fuRootTimeProfileStart(const char* lable);

/**
 \brief Stop time profile root node
 \param lable - lable name.
 \return void.
*/
FUNAMA_API void fuRootTimeProfileStop(const char* lable);

/**
 \brief Start time profile stack node
 \param lable - lable name.
 \return void.
*/
FUNAMA_API void fuStackTimeProfileStart(const char* lable);

/**
 \brief Stop time profile stack node
 \param lable - lable name.
 \return void.
*/
FUNAMA_API void fuStackTimeProfileStop(const char* lable);

FUNAMA_API void fuFrameTimeProfileRelaseMemory();

#ifdef __cplusplus
}
#endif
#endif