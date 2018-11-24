#ifndef FILE_HASH_
#define FILE_HASH_

/**
 * @file file_hash.h
 * This file includes function to computes hash
 * for the files at specified path.
 */

#include <string>

namespace dfr
{
/**
 * A class enapsulating the available hash functions.
 */
class hash
{
public:

  /**
     * A public static method.
     * This method computes the MD5 hash of file specified in the arguments.
     * File read buffer is initially set to _1 << 15_ which can be changed.
     * If hash could not be computed an empty string is returned.
     * @param path Path of the file for which MD5 is to be computed.
     * @param BUFFER_LENGTH Buffer size in which file is read.
     * @result MD5 hash of the file as <code>std::string</code>
     */
  static std::string MD5(const std::string &path, const size_t &BUFFER_LENGTH = 1 << 15);

  /**
     * A public static method.
     * This method computes the SHA256 hash of file specified in the arguments.
     * File read buffer is initially set to _1 << 15_ which can be changed.
     * If hash could not be computed an empty string is returned.
     * @param path Path of the file for which SHA256 is to be computed.
     * @param BUFFER_LENGTH Buffer size in which file is read.
     * @result SHA256 hash of the file as <code>std::string</code>
     */
  static std::string SHA256(const std::string &path, const size_t &BUFFER_LENGTH = 1 << 15);
};
}

#endif
