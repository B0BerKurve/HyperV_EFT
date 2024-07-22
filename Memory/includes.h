#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include <cstdint> // uintptr_t abuse
#include <cmath>

#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <algorithm>

#include "singleton.h"


#define IMGUI_DEFINE_MATH_OPERATORS



#include <d3d9.h>
#include <DirectXMath.h>



#ifdef _DEBUG
#define WRAP_IF_DEBUG(x) { x };
#else
#define WRAP_IF_DEBUG(x)
#endif
#define ERROR_MESSAGE(x) MessageBoxA(NULL, x, NULL, NULL)