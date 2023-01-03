#include "service.hpp"

bool service::RegisterAndStart(const std::wstring& driver_path) {
	const static DWORD ServiceTypeKernel = 1;
	const std::wstring driver_name = intel_driver::GetDriverNameW();
	const std::wstring servicesPath = XorStr(L"SYSTEM\\CurrentControlSet\\Services\\").c_str() + driver_name;
	const std::wstring nPath = XorStr(L"\\??\\").c_str() + driver_path;

	HKEY dservice;
	LSTATUS status = RegCreateKeyW(HKEY_LOCAL_MACHINE, servicesPath.c_str(), &dservice); //Returns Ok if already exists
	if (status != ERROR_SUCCESS) {
		return false;
	}

	status = RegSetKeyValueW(dservice, NULL, XorStr(L"ImagePath").c_str(), REG_EXPAND_SZ, nPath.c_str(), (DWORD)(nPath.size() * sizeof(wchar_t)));
	if (status != ERROR_SUCCESS) {
		RegCloseKey(dservice);
		return false;
	}
	
	status = RegSetKeyValueW(dservice, NULL, XorStr(L"Type").c_str(), REG_DWORD, &ServiceTypeKernel, sizeof(DWORD));
	if (status != ERROR_SUCCESS) {
		RegCloseKey(dservice);
		return false;
	}
	
	RegCloseKey(dservice);

	HMODULE ntdll = GetModuleHandleA(XorStr("ntdll.dll").c_str());
	if (ntdll == NULL) {
		return false;
	}

	auto RtlAdjustPrivilege = (nt::RtlAdjustPrivilege)GetProcAddress(ntdll, XorStr("RtlAdjustPrivilege").c_str());
	auto NtLoadDriver = (nt::NtLoadDriver)GetProcAddress(ntdll, XorStr("NtLoadDriver").c_str());

	ULONG SE_LOAD_DRIVER_PRIVILEGE = 10UL;
	BOOLEAN SeLoadDriverWasEnabled;
	NTSTATUS Status = RtlAdjustPrivilege(SE_LOAD_DRIVER_PRIVILEGE, TRUE, FALSE, &SeLoadDriverWasEnabled);
	if (!NT_SUCCESS(Status)) {
		return false;
	}

	std::wstring wdriver_reg_path = XorStr(L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\").c_str() + driver_name;
	UNICODE_STRING serviceStr;
	RtlInitUnicodeString(&serviceStr, wdriver_reg_path.c_str());

	Status = NtLoadDriver(&serviceStr);
	
	//Never should occur since kdmapper checks for "IsRunning" driver before
	if (Status == 0xC000010E) {// STATUS_IMAGE_ALREADY_LOADED
		return true;
	}
	
	return NT_SUCCESS(Status);
}

bool service::StopAndRemove(const std::wstring& driver_name) {
	HMODULE ntdll = GetModuleHandleA(XorStr("ntdll.dll").c_str());
	if (ntdll == NULL)
		return false;

	std::wstring wdriver_reg_path = XorStr(L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\").c_str() + driver_name;
	UNICODE_STRING serviceStr;
	RtlInitUnicodeString(&serviceStr, wdriver_reg_path.c_str());

	HKEY driver_service;
	std::wstring servicesPath = XorStr(L"SYSTEM\\CurrentControlSet\\Services\\").c_str() + driver_name;
	LSTATUS status = RegOpenKeyW(HKEY_LOCAL_MACHINE, servicesPath.c_str(), &driver_service);
	if (status != ERROR_SUCCESS) {
		if (status == ERROR_FILE_NOT_FOUND) {
			return true;
		}
		return false;
	}
	RegCloseKey(driver_service);

	auto NtUnloadDriver = (nt::NtUnloadDriver)GetProcAddress(ntdll, XorStr("NtUnloadDriver").c_str());
	NTSTATUS st = NtUnloadDriver(&serviceStr);
	if (st != 0x0) {
		status = RegDeleteKeyW(HKEY_LOCAL_MACHINE, servicesPath.c_str());
		return false; //lets consider unload fail as error because can cause problems with anti cheats later
	}
	

	status = RegDeleteKeyW(HKEY_LOCAL_MACHINE, servicesPath.c_str());
	if (status != ERROR_SUCCESS) {
		return false;
	}
	return true;
}
