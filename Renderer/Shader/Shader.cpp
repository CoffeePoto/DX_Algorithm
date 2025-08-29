#include "Shader.h"

Shader::Shader(const wchar_t* filename)
{
	wchar_t Filename[50] = {};
	wsprintf(Filename, L"%sVS.hlsl", filename);

	HRESULT result = D3DCompileFromFile(
		Filename, nullptr, nullptr,
		"main", "vs_5_0", 0, 0,
		&vertexShaderBuffer, nullptr
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	result = Engine::Get().GetDevice()->CreateVertexShader(
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		nullptr,
		&vertexShader
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	//inputlayout : vertex buffer의 데이터 구조를 설명해주는 정보를 담고 있다.
	D3D11_INPUT_ELEMENT_DESC inputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	result = Engine::Get().GetDevice()->CreateInputLayout(
		inputDesc, _countof(inputDesc),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&inputlayout
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	//pixel shader 컴파일 후 생성
	wsprintf(Filename, L"%sPS.hlsl", filename);
	result = D3DCompileFromFile(
		Filename, nullptr, nullptr,
		"main", "ps_5_0", 0, 0,
		&pixelShaderBuffer, nullptr
	);

	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	result = Engine::Get().GetDevice()->CreatePixelShader(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(),
		nullptr,
		&pixelShader
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
}

Shader::~Shader()
{
	SafeRelease(vertexShaderBuffer);
	SafeRelease(pixelShaderBuffer);
	SafeRelease(vertexShader);
	SafeRelease(pixelShader);
	SafeRelease(inputlayout);

}

void Shader::Bind()
{
	//입력 어셈블러에 조립(연결)
	Engine::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Engine::Get().GetContext()->VSSetShader(vertexShader, nullptr, 0);
	Engine::Get().GetContext()->IASetInputLayout(inputlayout);
	Engine::Get().GetContext()->PSSetShader(pixelShader, nullptr, 0);
}
