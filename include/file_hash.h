#ifndef FILE_HASH_
#define FILE_HASH_
#include <string>

namespace dfr
{
class hash
{
  public:
    static std::string MD5(const std::string &path, const size_t &BUFFER_LENGTH = 1 << 15);
};
}

#endif