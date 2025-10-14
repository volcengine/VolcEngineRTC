#ifndef MD5_H
#define MD5_H

#include <string>

// Message-Digest Hash Algorithm 5 (md5)
class md5
{
public:
    md5();
    static std::string calculate(const std::string&);
};

#endif // MD5_H
