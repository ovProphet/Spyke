#include "stdafx.h"
using namespace std;
using namespace boost::filesystem;

bool PathContainsName(string characters, path file_path);
void FindByFilename(string characters, path dir_path, vector<pair<string,bool>>& files);