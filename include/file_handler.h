#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <string>
#include <set>
#include <list>
#include <map>
#include <functional>
#include <boost/filesystem.hpp>

namespace dfr
{
/**
 * A Struct.
 * Structure to hold metadata of the file to be hashed.
 */
struct file_data
{
	std::string name; ///name of the file.
	std::string path; ///path of the file.
	std::string hash; ///hash of the file.
	uintmax_t size; ///size of the file.

	/**
	 * A constructor.
	 * Constructs a struct type object to store file metadata.
	 * @param[in] name Name of the file.
	 * @param[in] size Size of the file.
	 * @param[in] path Path of the file.
	 */ 
	file_data(const std::string &name, const uintmax_t &size, const std::string &path);
};

/**
 * A class.
 * This class stores the metadata of all the files and
 * includes function to operate on them based on the
 * specified command line parameters.
 */ 
class file_handler
{
	///A hashmap that maps list of files against their hash values(MD5).
	std::map<std::string, std::list<file_data>> file_map; 
	
	///The directory to be scanned.
	std::string directory; 
	
	///Total number of files for which hash was generated.
	size_t hashed_file_ct; 
	
	/**
	 * A list of extensions to filter the files based on extensions.
	 * If no extension was provided then all the files are scanned.
	 */ 
	std::set<std::string> exten;  

	/**
	 * A private method.
	 * Uses <code>boost::filesystem</code> to iterate through the specified directory
	 * and compute hash for each matching file. It does so in 2 passes.
	 * In the first pass: a count for the files is generated to show progress.
	 * In the second pass: actual work(hash computation) is done.
	 */ 
	void init_dir_load();
	
	/**
	 * A private method.
	 * A general routine that helps traverse files in a directory recursively.
	 * Called by @see init_dir_load() twice for traversal.
	 * @param[in] fx A lamda/callback to perform operation when a matching file is found.
	 * @result Returns the number of files successfully scanned.
	 */ 
	size_t dir_traverse_routine(const std::function<void(const size_t&, const boost::filesystem::path &)> &fx);
	
	/**
	 * A private method.
	 * It clears the @see file_map.
	 * Also, it sets @see hashed_file_ct to zero.
	 * @see init_dir_load()
	 * @see remove_in_place()
	 */ 
	void clean();
	
  public:
	
	/**
	 * A public method.
	 * Function to add the provided extension to the list of extensions.
	 * The correct format for extension is without the preceding dot('.').
	 * @param[in] ext Extension for file.
	 */ 
	void add_extension(const std::string &ext);
	
	/**
	 * A public constructor.
	 */ 
	file_handler();
	
	/**
	 * A public constructor.
	 * It takes path as an argument to set the @see directory to be scanned.
	 * @param path Path of directory to be loaded.
	 */ 
	file_handler(const std::string &path);
	
	/**
	 * A public method.
	 * @see file_handler(const std::string &path)
	 */ 
	void set_directory(const std::string &path);
	
	/**
	 * A public method.
	 * This function returns the value of files for which hash was
	 * computed.
	 * @result Value of @see hashed_file_ct.
	 */ 
	size_t total_hashed_file_count();
	
	/**
	 * A public method.
	 * @result Returns the count of unique files.
	 */ 
	size_t distinct_file_count();

	/**
	 * A public method.
	 * Initalizes the reading of directory files.
	 * Performs check if the set directory is actually a directory
	 * and that it is not empty.
	 * 
	 * @see init_dir_load()
	 * @result Returns true if scan was successful.
	 */
	bool load_directory();

	/**
	 * A public method.
	 * This function generates log/stats for all the files evaluated
	 * and writes them to the file name provided as an argument. If 
	 * no argument is supplied then log is written to <code>dupl_file.txt</code>
	 * in the current directory.
	 * @param out_file Name/Location of output file.
	 * @result Returns true if file was successfully opened and writted to.
	 */ 
	bool generate_list(const std::string &out_file = "dupl_file.txt");
	
	/**
	 * A public method.
	 * This function removes the duplicate files so found.
	 * There is no way of ensuring which file will be kept and which of the
	 * duplicates will be removed.
	 * If all the duplicates are removed successfully then it returns true.
	 * @result Returns true if all duplicates are removed.
	 */ 
	bool remove_in_place();
};
}
#endif