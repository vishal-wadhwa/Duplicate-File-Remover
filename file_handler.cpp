#include "file_handler.h"
#include <boost/filesystem.hpp>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>

std::string file_data::md5gen(const size_t &BUFFER_LENGTH)
{
	std::ifstream fi(path, std::ios::binary);

	if (!fi.is_open())
	{
		std::cerr << "Could not open: " + path << std::endl;
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

file_data::file_data(const std::string &name,
					 const uintmax_t &size,
					 const std::string &path) : name(name), path(path), size(size)
{
	hash = md5gen();
}

file_handler::file_handler(const std::string &path) : directory(path) {}

file_handler::file_handler() {}

void file_handler::add_extension(const std::string &ext)
{
	if (!ext.empty())
		exten.insert(exten.end(), "." + ext);
}

bool file_handler::set_directory(const std::string &path)
{
	directory = path;
	return !path.empty();
}

size_t file_handler::total_file_count()
{
	return tot_file_count;
}

size_t file_handler::distinct_file_count()
{
	return file_map.size();
}

bool file_handler::load_directory()
{
	try
	{

		if (exten.empty())
			throw std::string("Extensions not set.");
		if (directory.empty())
			throw std::string("Directory not set.");
		boost::filesystem::path p(directory);
		if (!boost::filesystem::is_directory(p))
			throw std::string(directory + " is not a directory.");

		init_dir_load();
	}
	catch (const std::string &e)
	{
		std::cerr << e << std::endl;
		return false;
	}
	return true;
}

void file_handler::init_dir_load()
{
	using namespace boost::filesystem;
	using rdit = recursive_directory_iterator;

	size_t curf = 0;
	path p(directory);

	for (rdit it(p); it != rdit(); ++it)
	{
		const path &curp = it->path();
		if (is_regular_file(curp) &&
			curp.has_extension() &&
			find(exten.begin(), exten.end(), curp.extension().string()) != exten.end())
			++tot_file_count;
	}

	if (total_file_count() == 0)
	{
		std::cerr << "No matching file found.\n";
		return;
	}

	size_t upd_inter = cbrt(total_file_count());

	for (rdit it(p); it != rdit(); ++it)
	{

		const path &curp = it->path();
		if (is_regular_file(curp) &&
			curp.has_extension() &&
			find(exten.begin(), exten.end(), curp.extension().string()) != exten.end())
		{
			++curf;

			if (curf % upd_inter == 0)
			{
				std::cout << "Computing hash for " << curf << " of "
						  << total_file_count() << " files.       \r";
				fflush(stdout);
			}
			file_data fd = file_data(
				curp.filename().string(),
				file_size(curp),
				curp.is_absolute()
					? "/" + curp.relative_path().string()
					: curp.relative_path().string());
			std::list<file_data> &dt = file_map[fd.hash];
			dt.insert(dt.end(), fd);
		}
	}
	std::cout << "Computing hash for " << curf << " of " << total_file_count()
			  << " files.       \r";
	std::cout << std::endl;
}

void file_handler::generate_list(const std::string &out_file)
{
	std::ofstream of(out_file);
	try
	{
		if (!of.is_open())
			throw std::string("Cannot open " + out_file);

		of << "=============  LIST OF FILES  =============\n\n";
		of << "Note: Duplicate files have been clubbed together.\n\n";
		of << "Total File Count: " << total_file_count() << "\n";
		of << "Distinct Image Count: " << distinct_file_count() << "\n";
		of << "Scanned Directory: " << directory << "\n\n";

		size_t ct = 1;
		of << std::fixed << std::setprecision(3);
		for (auto &dt : file_map)
		{
			std::list<file_data> &lfd = dt.second;
			of << "File No. " << ct << std::endl;

			for (file_data &fd : lfd)
			{
				of << '\t' << fd.name << ' ' << fd.path << ' ' << fd.size / 1024. << "kB\n";
				if (fd.hash.empty())
					throw std::string("Could not generate hash.");
			}
			of << std::endl;
			++ct;
		}
	}
	catch (const std::string &e)
	{
		std::cerr << e << std::endl;
	}
}

void file_handler::remove_in_place()
{
	using namespace boost::filesystem;
	for (auto &dt : file_map)
	{
		std::list<file_data> &lfd = dt.second;
		std::list<file_data>::iterator it = lfd.begin();
		for (++it; it != lfd.end(); ++it)
			if (!remove(path(it->path)))
				std::cerr << "Could not remove " << it->path << '\n';
	}
}
