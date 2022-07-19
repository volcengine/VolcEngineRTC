#ifndef __LICENCE_RESOURCES_PARSER__
#define __LICENCE_RESOURCES_PARSER__
/** @brief
 *  Resparser is used to parse merged resources.
 *  license should be merged
 *  into a single file with explicit version element. A merged resource should be
 *  write into file according to the following pattern:
 *  type(int)version(char[less than 255])len1(unsinged
 *  int)data(array[len1])len2(unsinged int)data(array[len2]) ...
 *  @author liuyang.10 2019.03.31
 */

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

#include "bef_effect_ai_public_define.h"

namespace labcv_license {

    typedef enum {
        ResourceType_Base = 0,
        ResourceType_MultiLicenseKey = 1,
        ResourceType_MultiLicenseKeyV1 = 2,
    } LicenseType;

    class BaseLicRes {
        // base class for resource
    public:
        BaseLicRes() {};

        ~BaseLicRes() {};

        int do_parse(const char *res_path, std::string version_string);
        int merge_files(const char *res_path, std::string version_string);

        std::string check_type(int type);

        int get_blocks_count() { return this->blocks_count; }

        void set_blocks_count(int blocks_counts) { this->blocks_count = blocks_counts; }


    protected:
        int read_data_block(FILE *fp,
                            void **param,
                            unsigned int &len,
                            unsigned int item_size);

        int read_data_block(void*& data,
                            int dataLen,
                            void** param,
                            unsigned int& len,
                            unsigned int item_size);

        int write_data_block(FILE *fp,
                             void *param,
                             unsigned int len,
                             unsigned int item_size);


    protected:
        virtual int get_res_type() = 0;

        virtual int init_data_buff(FILE *fp) = 0;
        virtual int init_data_buff(void*& data, int dataLen) = 0;

        virtual int merge_file(FILE *fp_out) = 0;  // tools to merge files

    public:
        static const int type = ResourceType_Base;

    protected:
        char version_buff[255];
        int blocks_count = 0;
    };

    class MultiLicRes : public BaseLicRes {
        // MultiLicRes
    public:
        MultiLicRes() {};

        virtual ~MultiLicRes();

        int get_function_license(unsigned int function_id, void **license, unsigned int &len);
        std::string get_license_version(){return std::string(version_buff);}

        int release();
        
        std::map<unsigned int, unsigned char *> function_lic_map;
        std::map<unsigned int, unsigned int> function_lic_len_map;

    protected:
        static const int type = ResourceType_MultiLicenseKey;


    
        //int param_block_num = 0;
        unsigned char **params_array = nullptr;
        unsigned int *param_len_array = nullptr;

        // virtual functions
        int get_res_type() { return this->type; };

        int init_data_buff(FILE *fp);
        int init_data_buff(void*& data, int dataLen);

        int merge_file(FILE *fp_out);  // temp tools to merge files
        int set_param_array(int param_block_num);
    };
    
    class MultiLicResV1 : public MultiLicRes {
        // MultiLicResV1
    public:
        MultiLicResV1() {};
        
        virtual ~MultiLicResV1();
        
        int do_parse(const char *res_path);
        int do_parse_buffer(void *buffer, size_t len);
        int do_parse(const char *res_path, std::string version_string);
        int merge_files(const char *res_path, std::string version_string);
    protected:
        static const int type = ResourceType_MultiLicenseKeyV1;
        int get_res_type() { return this->type; };
        
    };

}
#endif
