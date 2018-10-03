#include "../include/file_handler.h"
#include "../include/file_hash.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <functional>
#include <iomanip>
#include <queue>
#include<cmath>

dfr::file_data::file_data(const std::string &name,
						  const uintmax_t &size,
						  const std::string &path) : name(name), path(path), size(size)
{
	hash = dfr::hash::SHA256(path);
}

dfr::file_handler::file_handler(const std::string &path) : directory(path), hashed_file_ct(0) {}

dfr::file_handler::file_handler() : directory(""), hashed_file_ct(0) {}

void dfr::file_handler::add_extension(const std::string &ext)
{
	if (!ext.empty())
		exten.insert("." + ext);
}

void dfr::file_handler::set_directory(const std::string &path)
{
	directory = path;
}

size_t dfr::file_handler::total_hashed_file_count()
{
	return hashed_file_ct;
}

size_t dfr::file_handler::distinct_file_count()
{
	return file_map.size();
}

void dfr::file_handler::clean()
{
	file_map.clear();
	hashed_file_ct = 0;
}

bool dfr::file_handler::load_directory()
{
	try
	{
		if (directory.empty())
			throw std::string("Directory not set.");
		boost::filesystem::path p(directory);
		if (!boost::filesystem::is_directory(p))
			throw std::string(directory + " is not a directory.");

		init_dir_load();
	}
	catch (const std::string &e)
	{
#ifndef DEBUG
		std::cerr << e << std::endl;
#endif
		return false;
	}
	return true;
}

size_t dfr::file_handler::dir_traverse_routine(
	const std::function<
		void(const size_t &,
			 const boost::filesystem::path &)> &fx)
{
	using namespace boost::filesystem;
	using dit = directory_iterator; ///Alias for directory_iterator.

	size_t curf = 0;
	path p(directory);

	std::queue<path> dirs;
	dirs.push(p);

	while (!dirs.empty())
	{
		const path &curd = dirs.front();
		dit it;

		//can't access directory check
		try
		{
			it = dit(curd);
		}
		catch (const filesystem_error &)
		{
			it = dit();
		}
		dirs.pop();

		while (it != dit())
		{
			const path &curp = it->path();
			try
			{
				if (is_regular_file(curp))
				{
					if (exten.empty() || (curp.has_extension() &&
										  exten.find(curp.extension().string()) != exten.end()))
					{
						++curf;
						fx(curf, curp);
					}
				}
				else if (!is_symlink(curp) && is_directory(curp))
					dirs.push(curp);
			}
			catch (const filesystem_error &)
			{
			}
			++it;
		}
	}
	return curf;
}

void dfr::file_handler::init_dir_load()
{
	using namespace boost::filesystem;
	clean();
	size_t file_ct = 0, upd_inter = 0;

	///lambda for counting the files for progress
	const auto dum = [](const size_t &curf, const path &curp) {
		//kinda useless
		///suppresses compiler warning for unused variable.
		(void)curf;
		(void)curp;
	};
	file_ct = dir_traverse_routine(dum);

	if (file_ct == 0)
	{
#ifndef DEBUG
		std::cerr << "No matching file found.\n";
#endif
		return;
	}

	///Updates are printed to standard output in multiples of
	///cube root of number of files scanned.
	upd_inter = cbrt(file_ct);

	///lambda for progress update and hash generation.
	const auto build = [upd_inter, file_ct, this](const size_t &curf, const path &curp) {

#ifndef DEBUG
		if (curf % upd_inter == 0)
		{
			std::cout << "Checking file " << curf << " of "
					  << file_ct << " files.       \r";
			fflush(stdout);
		}
#endif
		file_data fd = file_data(
			curp.filename().string(),
			file_size(curp),
			curp.is_absolute()
				? "/" + curp.relative_path().string()
				: curp.relative_path().string());

		if (!fd.hash.empty())
		{
			std::list<file_data> &dt = file_map[fd.hash];
			dt.insert(dt.end(), fd);
			++hashed_file_ct;
		}
	};

	dir_traverse_routine(build);
#ifndef DEBUG
	std::cout << "Computed hash for " << hashed_file_ct << " of " << file_ct
			  << " files.       \r";
	std::cout << std::endl;
#endif
}

bool dfr::file_handler::generate_list(const std::string &out_file)
{
	std::ofstream of(out_file);
	try
	{
		if (!of.is_open())
			throw std::string("Cannot open output file: " + out_file);

		of << "=============  LIST OF FILES  =============\n\n";
		of << "Note: Duplicate files have been clubbed together.\n\n";
		of << "Total Files Read: " << total_hashed_file_count() << "\n";
		of << "Distinct File Count: " << distinct_file_count() << "\n";
		of << "Duplicate File Count: " << total_hashed_file_count() - distinct_file_count() << "\n";
		of << "Scanned Directory: " << directory << "\n\n";
		of << "Note: First file in each set of duplicates will be saved.\n\n";
		size_t ct = 1;
		of << std::fixed << std::setprecision(3);
		for (const auto &dt : file_map)
		{
			const std::list<file_data> &lfd = dt.second;

			if (lfd.size() == 1)
				continue;

			of << "File No. " << ct << std::endl;
			size_t pos = 0;
			for (const file_data &fd : lfd)
			{
				of << '\t' << fd.name << ' ' << fd.path
				   << ' ' << fd.size / 1024. << "kB " << '\n';
				++pos;
			}

			of << std::endl;
			++ct;
		}
	}
	catch (const std::string &e)
	{
#ifndef DEBUG
		std::cerr << e << std::endl;
#endif
		return false;
	}
	return true;
}

bool dfr::file_handler::remove_in_place()
{
	using namespace boost::filesystem;
	bool ok = true;
	for (const auto &dt : file_map)
	{
		const std::list<file_data> &lfd = dt.second;
		std::list<file_data>::const_iterator it = lfd.begin();
		for (++it; it != lfd.end(); ++it)
			if (!remove(path(it->path)))
			{
#ifndef DEBUG
				std::cerr << "Could not remove " << it->path << '\n';
#endif
				ok = false;
			}
	}
	clean();
	return ok;
}
