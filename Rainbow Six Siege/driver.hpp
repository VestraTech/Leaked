#pragma once
#include "globals.hpp"
#define code_virtual CTL_CODE(FILE_DEVICE_UNKNOWN, 0x972, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_physical CTL_CODE(FILE_DEVICE_UNKNOWN, 0x78c, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_image CTL_CODE(FILE_DEVICE_UNKNOWN, 0xf7d, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_security 0xafb14c4
#define physical_read 0x873 
#define physical_write 0xd6b
#define virtual_read 0x5bc
#define virtual_write 0x7cd

typedef struct t_virtual {
	INT32 security_code;
	INT32 process_id;
	INT32 virtual_mode;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
} e_virtual, * s_virtual;

typedef struct t_physical {
	INT32 security_code;
	INT32 process_id;
	INT32 physical_mode;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
} e_physical, * s_physical;

typedef struct t_image {
	INT32 security_code;
	INT32 process_id;
	ULONGLONG* address;
} e_image, * s_image;

namespace driver {
	HANDLE driver_handle;


	bool check() {
		driver_handle = CreateFile("\\\\.\\\FlashBois", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}

	void read_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = sdk::process_id;
		arguments.virtual_mode = virtual_read;

		DeviceIoControl(driver_handle, code_virtual, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void write__memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = sdk::process_id;
		arguments.virtual_mode = virtual_write;

		DeviceIoControl(driver_handle, code_virtual, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void read_physical_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = sdk::process_id;
		arguments.virtual_mode = physical_read;

		DeviceIoControl(driver_handle, code_physical, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void write_physical_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = sdk::process_id;
		arguments.virtual_mode = physical_write;

		DeviceIoControl(driver_handle, code_physical, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	uintptr_t get_moudle_base() {
		uintptr_t image_address = { NULL };
		t_image arguments = { NULL };

		arguments.security_code = code_security;
		arguments.process_id = sdk::process_id;
		arguments.address = (ULONGLONG*)&image_address;

		DeviceIoControl(driver_handle, code_image, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}

	INT32 get_procces(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					sdk::process_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);


		return { NULL };
	}
}

template <typename T>
T read(uint64_t address) {
	T buffer{ };
	driver::read_memory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template<typename T>
void write(uint64_t address, T buffer) {
	driver::write__memory((PVOID)address, &buffer, sizeof(T));
}

template <typename T>
T read_dv(uint64_t address) {
	T buffer{ };
	driver::read_physical_memory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template<typename T>
void write_on(uint64_t address, T buffer) {
	driver::write_physical_memory((PVOID)address, &buffer, sizeof(T));
}

