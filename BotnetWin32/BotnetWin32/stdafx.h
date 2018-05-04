// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma warning(disable : 4996)

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <winsock2.h>
#include <windows.h>
#include <winver.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <atlstr.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <AclAPI.h>
#include "Sddl.h"
#include <io.h>
#include <fstream>
#include <urlmon.h>
#include <iostream>
#include <functional>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>
#include <Lmcons.h>
#include <sstream>
#include <curl/curl.h>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

// TODO: reference additional headers your program requires here

#include <stdio.h>
#include <string>

typedef NTSTATUS(WINAPI *_ZwAllocateVirtualMemory) (
	_In_    HANDLE    ProcessHandle,
	_Inout_ PVOID     *BaseAddress,
	_In_    ULONG_PTR ZeroBits,
	_Inout_ PSIZE_T   RegionSize,
	_In_    ULONG     AllocationType,
	_In_    ULONG     Protect
	);

typedef NTSTATUS(WINAPI *_PsLookupProcessByProcessId) (
	_In_  HANDLE ProcessId,
	_Out_ PVOID  *Process
	);

typedef PACCESS_TOKEN(WINAPI *_PsReferencePrimaryToken) (
	_Inout_ PVOID Process
	);

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemModuleInformation = 11
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI *_ZwQuerySystemInformation) (
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
	);

typedef struct _SYSTEM_MODULE_INFORMATION_ENTRY {
	HANDLE Section;
	PVOID  MappedBase;
	PVOID  Base;
	ULONG  Size;
	ULONG  Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT PathLength;
	CHAR   ImageName[256];
} SYSTEM_MODULE_INFORMATION_ENTRY, *PSYSTEM_MODULE_INFORMATION_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION {
	ULONG Count;
	SYSTEM_MODULE_INFORMATION_ENTRY Module[1];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;

#define ID_TIMER    0x1
#define WM_SYSTIMER 0x118