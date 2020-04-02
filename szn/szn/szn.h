#pragma comment(lib, "libMinHook-x86-v141-mt.lib")
#pragma comment ( lib, "WinMM.lib" )

#include <Windows.h>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <stdio.h>
#include <type_traits>
#include <vector>
#include <map>
#include <string>
#include <Psapi.h>
#include <Mmsystem.h>
#include <immintrin.h>
#include <iostream>

#include <sstream>
#include <iomanip>

#include "Detours.h"
#include "MinHook.h"

using namespace std;
using namespace chrono;

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"

#include "Math.h"

#include "Structs.h"
#include "cvars.h"
#include "Memory.h"
#include "Console.h"

#include "Rendering.h"
#include "Engine.h"
#include "Visuals.h"

#include "Aimbot.h"
#include "Anti-Aim.h"

#include "D3D.h"
#include "Hooking.h"