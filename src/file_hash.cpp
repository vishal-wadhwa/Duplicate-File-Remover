#include "../include/file_hash.h"
#include <sstream>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <iomanip>

/**
 * Hash generation function.
 * Uses openssl/md5 to generated hash.
 */
std::string dfr::hash::MD5(const std::string &path, const size_t &BUFFER_LENGTH)
{
    std::ifstream fi(path, std::ios::binary);

    if (!fi.is_open())
    {
#ifndef DEBUG
        std::cerr << "Could not read: " + path << std::endl;
#endif
        return "";
    }

    char *buffer = new char[BUFFER_LENGTH];
    unsigned char result[MD5_DIGEST_LENGTH];

    MD5_CTX ctx;
    MD5_Init(&ctx);

    while (fi)
    {
        fi.read(buffer, BUFFER_LENGTH);
        MD5_Update(&ctx, buffer, fi.gcount());
    }

    MD5_Final(result, &ctx);

    std::ostringstream sout;
    sout << std::hex << std::setfill('0');
    for (auto c : result)
        sout << std::setw(2) << (int)c;

    fi.close();
    delete buffer;
    return sout.str();
}

/**
 * Hash generation function.
 * Uses openssl/sha256 to generated hash.
 */
std::string dfr::hash::SHA256(const std::string &path, const size_t &BUFFER_LENGTH)
{
    std::ifstream fi(path, std::ios::binary);

    if (!fi.is_open())
    {
#ifndef DEBUG
        std::cerr << "Could not read: " + path << std::endl;
#endif
        return "";
    }

    char *buffer = new char[BUFFER_LENGTH];
    unsigned char result[SHA256_DIGEST_LENGTH];

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while (fi)
    {
        fi.read(buffer, BUFFER_LENGTH);
        SHA256_Update(&ctx, buffer, fi.gcount());
    }

    SHA256_Final(result, &ctx);

    std::ostringstream sout;
    sout << std::hex << std::setfill('0');
    for (auto c : result)
        sout << std::setw(2) << (int)c;
    fi.close();
    delete buffer;
    return sout.str();
}
