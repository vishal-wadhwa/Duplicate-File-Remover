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
struct file_data
{
	std::string name, path, hash;
	uintmax_t size;
	file_data(const std::string &name, const uintmax_t &size, const std::string &path);
};

class file_handler
{
	std::map<std::string, std::list<file_data>> file_map;
	std::string directory;
	size_t hashed_file_ct;
	std::set<std::string> exten;
	void init_dir_load();
	size_t dir_traverse_routine(const std::function<void(const size_t&, const boost::filesystem::path &)> &fx);
	void clean();
	
  public:
	void add_extension(const std::string &ext);
	file_handler();
	file_handler(const std::string &path);
	void set_directory(const std::string &path);
	size_t total_hashed_file_count();
	size_t distinct_file_count();
	bool load_directory();
	bool generate_list(const std::string &out_file = "dupl_file.txt");
	bool remove_in_place();
};
}
#endif