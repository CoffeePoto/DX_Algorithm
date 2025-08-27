#include "Engine.h"
#include "Mesh/RectMesh.h"

Engine* Engine::instance = nullptr;

LRESULT Engine::MsgProcess(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		if (wparam == VK_ESCAPE)
		{
			if (MessageBoxA(nullptr, "Do you want to Quit?", "Quit?", MB_YESNO) == IDYES)
			{
				DestroyWindow(hwnd);
				return 0;
			}
		}
		break;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}

Engine::Engine(uint32 width, uint32 height, HINSTANCE hInstance)
{
	instance = this;

	window = new Window(width, height, hInstance, MsgProcess);

	uint32 flag = 0;
#if _DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featurelevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	//��ġ �ʱ�ȭ
	//device ����
	HRESULT result = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, featurelevels, _countof(featurelevels),
		D3D11_SDK_VERSION, &device, nullptr, &context
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	//����ü�� ����
	IDXGIFactory* factory = nullptr;
	result = CreateDXGIFactory(IID_PPV_ARGS(&factory));
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.BufferCount = 1;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.BufferDesc.Width = window->GetWidth();
	swapchainDesc.BufferDesc.Height = window->GetHeight();
	swapchainDesc.OutputWindow = window->GetHandle();
	swapchainDesc.Windowed = true;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	result = factory->CreateSwapChain(device, &swapchainDesc, &swapChain);
	if (FAILED(result))
	{
		SafeRelease(factory);
		__debugbreak();
		return;
	}
	SafeRelease(factory);

	ID3D11Texture2D* backbuffer;
	result = swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
	//rtv ����
	result = device->CreateRenderTargetView(backbuffer, nullptr, &RenderTargetView);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	SafeRelease(backbuffer);

	//viewport ����
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)window->GetWidth();
	viewport.Height = (float)window->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
	//mesh = new RectMesh();
	//shader = new Shader(L"HLSLShaders/Default");
}

Engine::~Engine()
{
	SafeDelete(window);
	//SafeDelete(mesh);
	//SafeDelete(shader);

	SafeRelease(device);
	SafeRelease(RenderTargetView);
	SafeRelease(swapChain);
	SafeRelease(context);
}

void Engine::Run()
{
	//Todo: ������ ����ϰ� ���� ���� ����
	LARGE_INTEGER frequency = {};
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER currentTime = {};
	LARGE_INTEGER previousTime = {};
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	float targetFrameRate = 120.0f;
	float oneFrameTime = 1.0f / targetFrameRate;
	
	//�޽��� ó��
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//basic gameloop ����
			QueryPerformanceCounter(&currentTime);
			float deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;
			if (deltaTime >= oneFrameTime)
			{
				Update(deltaTime);
				Render();
				if (mainLevel)
				{
					mainLevel->ProcessAddAndDeleteActor();
				}

				ProcessLevelTransition();
			}
		}
	}
}

void Engine::AddLevel(Level* newLevel)
{
	changeLevel = newLevel;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::Update(float deltaTime)
{
	if (mainLevel)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Render()
{
	//����
	float backgroundColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	BeginDraw(backgroundColor);
	Draw();
	EndDraw();

}

void Engine::BeginDraw(float* backgroundColor)
{
	//rtv backbuffer�� ����ϰ� ��� ���� ����
	context->OMSetRenderTargets(1, &RenderTargetView, nullptr);
	context->ClearRenderTargetView(RenderTargetView, backgroundColor);
}

void Engine::Draw()
{
	////���̴� ���ε��ϰ� �޽� �׸���
	//shader->Bind();
	//mesh->Draw();
	if (mainLevel)
	{
		mainLevel->Draw();
	}
}

void Engine::EndDraw()
{
	//����ü�� back-front ��ȯ
	swapChain->Present(0, 0);
}

void Engine::ProcessLevelTransition()
{
	if (changeLevel)
	{
		if (mainLevel)
		{
			SafeDelete(mainLevel);
		}

		mainLevel = changeLevel;
		changeLevel = nullptr;
	}
}