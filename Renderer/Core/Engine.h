#pragma once

#include "Utils.h"
#include "Window.h"
#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

class Engine
{
public:
	Engine(uint32 width, uint32 height, HINSTANCE HInstance);

	~Engine();

	void Run();
	void AddLevel(Level*);
	static Engine& Get();

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetContext() const { return context; }

private:
	static LRESULT MsgProcess(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	void Update(float deltaTime);
	void Render();

	void BeginDraw(float* backgroundColor);
	void Draw();
	void EndDraw();
	void ProcessLevelTransition();

private:
	Window* window = nullptr;
	Level* mainLevel = nullptr;
	Level* changeLevel = nullptr;

	// 리소스.
	ID3D11Device* device = nullptr;				// 리소스 생성.
	ID3D11DeviceContext* context = nullptr;		// 바인딩/드로우.
	IDXGISwapChain* swapChain = nullptr;		// 버퍼교환.

	ID3D11RenderTargetView* RenderTargetView;
	CD3D11_VIEWPORT viewport = { };

	static Engine* instance;
};