#pragma once

#include "Utils.h"
#include "Window.h"
#include "Camera.h"
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
	XMMATRIX GetWorldMatrix() const { return worldMatrix; }
	XMMATRIX GetProjectionMatrix() const { return projectionMatrix; }
	XMMATRIX GetViewMatrix() const { return viewMatrix; }

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

	// ���ҽ�.
	ID3D11Device* device = nullptr;				// ���ҽ� ����.
	ID3D11DeviceContext* context = nullptr;		// ���ε�/��ο�.
	IDXGISwapChain* swapChain = nullptr;		// ���۱�ȯ.

	ID3D11RenderTargetView* RenderTargetView;
	CD3D11_VIEWPORT viewport = { };

	XMMATRIX worldMatrix = { };
	XMMATRIX projectionMatrix = { };
	XMMATRIX orthoMatrix = { };
	XMMATRIX viewMatrix = { };

	static Engine* instance;
};