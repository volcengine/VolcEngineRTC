#include "md5.h"

#include <iostream>
#include <iomanip>
#include <openssl/md5.h>
#include <sstream>

md5::md5() {}

// Message-Digest Hash Algorithm 5 (md5)
std::string md5::calculate(const std::string& input) {
    unsigned char digest[MD5_DIGEST_LENGTH];

    // Compute hash
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input.c_str(), input.length());
    MD5_Final(digest, &context);

    // // Convert the digest into the hex string
    std::ostringstream result;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        result << std::setw(2) << std::setfill('0') << std::hex << (int)digest[i];
    }

    return result.str();
}
