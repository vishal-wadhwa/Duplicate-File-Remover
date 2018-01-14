#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <string>
#include <list>
#include <map>

struct file_data
{
	std::string name, path, hash;
	uintmax_t size;
	file_data(const std::string &name, const uintmax_t &size, const std::string &path);

  private:
	std::string md5gen(const size_t &BUFFER_LENGTH = 1 << 15);
};

class file_handler
{
	std::map<std::string, std::list<file_data>> file_map;
	size_t tot_file_count;
	std::string directory;
	std::list<std::string> exten;
	void init_dir_load();

  public:
	void add_extension(const std::string &ext);
	file_handler();
	file_handler(const std::string &path);
	bool set_directory(const std::string &path);
	size_t total_file_count();
	size_t distinct_file_count();
	bool load_directory();
	void generate_list(const std::string &out_file = "dupl_file.txt");
	void remove_in_place();
};
#endif