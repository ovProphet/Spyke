#include "stdafx.h"
#include "DirectoryTraversal.h"
#include "Connection.h"

bool PathContainsName(string characters, path file_path)
{
	string buffer = file_path.generic_string();
	return buffer.find(characters) != string::npos;
}
void FindByFilename(string characters, path dir_path, vector<string>& files)
{
	boost::system::error_code ec;
	vector<boost::filesystem::path> result;
	if (!exists(dir_path)) return;
	directory_iterator end_itr; // default construction yields past-the-end
	for (directory_iterator itr(dir_path, ec); itr != end_itr; ++itr)
	{
		if (ec)
			continue;
		if (is_directory(itr->status()))
		{
			FindByFilename(characters, itr->path(), files);
		}
		else if (PathContainsName(characters, itr->path())) // see below
		{
			files.push_back((itr->path()).generic_string());
		}
	}
}
