#pragma once

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "winmm.lib")

#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>
#include <d3dcompiler.h>

#include "Math/Math.h"

using int32 = __int32;
using int64 = __int64;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

template<typename T>
void SafeRelease(T*& pointer)
{
	if (pointer)
	{
		pointer->Release();
		pointer = nullptr;
	}

}