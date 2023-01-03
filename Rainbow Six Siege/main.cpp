#include <Windows.h>
#include <string>

#include "auth.hpp"
#include "vmprotect.hpp"
#include "xorstr.hpp"
#include "kdmapper/kdmapper.hpp"
#include "driver.hpp"
#include "globals.hpp"
#include "offsets.h"
#include "esp.hpp"

using namespace KeyAuth;

std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = XorStr("https://keyauth.win/api/1.2/").c_str();

api server(name, ownerid, secret, version, url);
HANDLE iqvw64e_device_handle;

typedef struct info_t {
	int pid = 0;
	DWORD_PTR address;
	void* value;
	SIZE_T size;
	void* data;
}	info, * p_info;

int paramExists(const int argc, wchar_t** argv, const wchar_t* param) {
	size_t plen = wcslen(param);
	for (int i = 1; i < argc; i++) {
		if (wcslen(argv[i]) == plen + 1ull && _wcsicmp(&argv[i][1], param) == 0 && argv[i][0] == '/') { // with slash
			return i;
		}
		else if (wcslen(argv[i]) == plen + 2ull && _wcsicmp(&argv[i][2], param) == 0 && argv[i][0] == '-' && argv[i][1] == '-') { // with double dash
			return i;
		}
	}
	return -1;
}

bool callbackExample(ULONG64* param1, ULONG64* param2, ULONG64 allocationPtr, ULONG64 allocationSize, ULONG64 mdlptr) {
	UNREFERENCED_PARAMETER(param1);
	UNREFERENCED_PARAMETER(param2);
	UNREFERENCED_PARAMETER(allocationPtr);
	UNREFERENCED_PARAMETER(allocationSize);
	UNREFERENCED_PARAMETER(mdlptr);
	return true;
}
int main(const int argc, wchar_t** argv)
{
	VMProtectBeginUltra(XorStr("main").c_str());

	SetConsoleTitleA(XorStr("Vestra").c_str());
	std::cout << XorStr("license Key: ");
	std::string key;
	std::cin >> key;
	server.connect();
	if (!server.data.success) {
		system(XorStr("cls").c_str());
		std::cout << XorStr("failed to connect to server!");
		Sleep(3500);
		exit(0);
	}
	else if (server.data.success) {
		if (server.data.version == server.version) {
		}
		else {
			exit(0);
		}
		server.login(key);
		if (!server.data.success) {
			system(XorStr("cls").c_str());
			std::cout << XorStr("failed to connect to server!");
			Sleep(3500);
			exit(0);
		}
		else if (server.data.success) {
			if (server.data.subscriptions[0] == XorStr("default").c_str()) {
	
				bool free = paramExists(argc, argv, L"free") > 0;
				bool mdlMode = paramExists(argc, argv, L"mdl") > 0;
				bool passAllocationPtr = paramExists(argc, argv, L"PassAllocationPtr") > 0;

				if (free) {
				}
				if (mdlMode) {
				}
				if (passAllocationPtr) {
				}

				if (!driver::check()) {
					std::vector<uint8_t> driver = server.download(XorStr("531929").c_str());

					iqvw64e_device_handle = intel_driver::Load();

					if (iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
						system(XorStr("cls").c_str());
						std::cout << XorStr("failed to load, error code: 1!");
						Sleep(3500);
						exit(0);
					}
					NTSTATUS exitCode = 0;
					if (!kdmapper::MapDriver(iqvw64e_device_handle, driver.data(), 0, 0, free, true, mdlMode, passAllocationPtr, callbackExample, &exitCode)) {
						system(XorStr("cls").c_str());
						std::cout << XorStr("failed to load, error code: 2!");
						Sleep(3500);
						exit(0);
					}
					if (!intel_driver::Unload(iqvw64e_device_handle)) {
						system(XorStr("cls").c_str());
						std::cout << XorStr("failed to load, error code: 3!");
						Sleep(3500);
						exit(0);
					}
				}
				::ShowWindow(::GetConsoleWindow(), SW_HIDE);
				MessageBoxA(NULL, XorStr("start rainbow six siege!").c_str(), NULL, NULL);
				HWND hwnd = NULL;
				DWORD processID;
				while (hwnd == NULL) {
					hwnd = FindWindowA(XorStr("R6Game").c_str(), XorStr("Rainbow Six").c_str());
					Sleep(1000);
				}
				GetWindowThreadProcessId(hwnd, &processID);
				info_t Input_Output_Data;
				Input_Output_Data.pid = processID;
				unsigned long int Readed_Bytes_Amount;

				if (!driver::get_procces(XorStr("RainbowSix.exe").c_str())) {
					system(XorStr("cls").c_str());
					MessageBoxA(NULL, XorStr("failed to load error code 4!").c_str(), NULL, NULL);
					exit(0);
				}
				sdk::module_base = driver::get_moudle_base();
				if (!sdk::module_base)
				{
					system(XorStr("cls").c_str());
					MessageBoxA(NULL, XorStr("restart the loader").c_str(), NULL, NULL);
					exit(0);
				}

				Beep(500, 500);

				while (true) {
					if (!FindWindowA(0, XorStr("Rainbow Six").c_str())) {
						MessageBoxA(NULL, XorStr("Unloaded").c_str(), NULL, NULL);
						exit(0);
					}
					esp::run();
				}
			}
		}
	}
	VMProtectEnd();
}