#include "Window.h"

Window::Window(uint32 width, uint32 height, HINSTANCE hInstance, WNDPROC messageproc)
	:width(width), height(height), instance(hInstance)
{
	size_t length = lstrlen(L"DirectX Windows") + 1;
	name = new wchar_t[length];
	lstrcpy(name, L"Coffeepott");

	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpfnWndProc = messageproc;
	wc.lpszClassName = L"CoffeePott";
	wc.style = CS_VREDRAW | CS_HREDRAW;

	//윈도우 클래스 등록
	if (!RegisterClass(&wc))
	{
		__debugbreak();
		return;
	}

	//실제 그려질 프레임의 크기를 결정: 지정한 수치가 스케치북 사이즈가 되도록 조절
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	uint32 windowWidth = rect.right - rect.left;
	uint32 windowHeight = rect.bottom - rect.top;

	//창이 화면 가운데 출력되도록 지정
	int xPosition = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
	int yPosition = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;

	handle = CreateWindow(
		wc.lpszClassName,
		name,
		WS_OVERLAPPEDWINDOW,
		xPosition, yPosition,
		windowWidth, windowHeight,
		nullptr, nullptr,
		instance,
		nullptr);

	if (!handle)
	{
		__debugbreak();
		return;
	}

	//윈도우 보여주기 설정
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}

Window::~Window()
{
	UnregisterClass(name, instance);
	SafeDelete(name);
}
