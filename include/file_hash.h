#include <string>
enum HASH_TYPE
{
    MD5,
    SHA1
};

//using different type of hashes
std::string compute_hash(std::string &path,
                         const size_t &BUFFER_SIZE = 1 << 15,
                         HASH_TYPE h)
{
    
}