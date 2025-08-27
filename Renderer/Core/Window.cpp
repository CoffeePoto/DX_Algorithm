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

	//������ Ŭ���� ���
	if (!RegisterClass(&wc))
	{
		__debugbreak();
		return;
	}

	//���� �׷��� �������� ũ�⸦ ����: ������ ��ġ�� ����ġ�� ����� �ǵ��� ����
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	uint32 windowWidth = rect.right - rect.left;
	uint32 windowHeight = rect.bottom - rect.top;

	//â�� ȭ�� ��� ��µǵ��� ����
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

	//������ �����ֱ� ����
	ShowWindow(handle, SW_SHOW);
	UpdateWindow(handle);
}

Window::~Window()
{
	UnregisterClass(name, instance);
	SafeDelete(name);
}
