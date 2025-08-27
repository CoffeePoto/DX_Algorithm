#pragma once

#include "Utils.h"

class Window
{

public:
	Window(uint32 width, uint32 height, HINSTANCE hInstance, WNDPROC messageproc);
	~Window();

	uint32 GetWidth() const { return width; }
	uint32 GetHeight() const { return height; }
	HWND GetHandle() const { return handle; }

private:
	wchar_t* name = nullptr;
	uint32 width = 0;
	uint32 height = 0;
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;
};