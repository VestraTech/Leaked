#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")

#include "render/imgui.h"
#include "render/imgui_impl_dx9.h"
#include "render/imgui_impl_win32.h"

#include "directx/d3dx9.h"
#pragma comment (lib, "d3d9.lib")

#define M_PI (double)3.1415926535
#define actor_player 4