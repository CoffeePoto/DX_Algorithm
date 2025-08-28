#pragma once

#include "Utils.h"
#include "Engine.h"

class Shader
{
public:
	Shader(const wchar_t* filename);
	virtual ~Shader();

	virtual void Bind();

private:
	struct MatrixType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

private:
	ID3D11VertexShader* vertexShader = nullptr;
	ID3DBlob* vertexShaderBuffer = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3DBlob* pixelShaderBuffer = nullptr;
	ID3D11InputLayout* inputlayout = nullptr;
	ID3D11Buffer* matrixBuffer = nullptr;
};
