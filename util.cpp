#include "util.h"


int toInt(const std::string& s)
{
    int ret = 0;
    for (int i = 0; i < s.size(); i++)
    {
        ret = ret * 10 + s[i] - '0';
    }
    return ret;
}
