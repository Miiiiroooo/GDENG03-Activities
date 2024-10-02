#include "Shader.h"
#include <d3dcompiler.h>
#include <algorithm>
#include <string>


#pragma region Shader methods
Shader::Shader(GraphicsEngine* gfx, LPCWSTR shaderFile) : AD3D11Object(gfx), shaderFile(shaderFile)
{

}

Shader::~Shader()
{

}

bool Shader::Release()
{
	delete this;
	return true;
}

LPCWSTR Shader::GetShaderFileName()
{
	/*std::wstring wStr(shaderFile);
	wStr.erase(wStr.find(L".cso"), 4);
	LPCWSTR shaderName = wStr.c_str();
	return shaderName;*/

	return shaderFile;
}
#pragma endregion


#pragma region VertexShader methods
VertexShader::VertexShader(GraphicsEngine* gfx, LPCWSTR shaderFile, const std::vector<D3D11_INPUT_ELEMENT_DESC>& inputElements) : Shader(gfx, shaderFile), inputElements(inputElements)
{

}

VertexShader::~VertexShader()
{

}

bool VertexShader::Init()
{
	Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob; 
	 
	if (FAILED(D3DReadFileToBlob(shaderFile, &shaderBlob))) 
	{
		return false;
	}
	 
	if (FAILED(gfx->GetDevice()->CreateVertexShader(shaderBlob.Get()->GetBufferPointer(), shaderBlob.Get()->GetBufferSize(), nullptr, &vShader)))
	{
		return false;
	}

	if (FAILED(gfx->GetDevice()->CreateInputLayout(inputElements.data(), inputElements.size(), shaderBlob.Get()->GetBufferPointer(), shaderBlob.Get()->GetBufferSize(), &inputLayout)))
	{
		return false;
	}

	shaderBlob.Get()->Release(); 

	return true;
}

void VertexShader::BindToPipeline()
{
	gfx->GetDeviceContext()->IASetInputLayout(inputLayout.Get());
	gfx->GetDeviceContext()->VSSetShader(vShader.Get(), nullptr, 0u);
}

bool VertexShader::Release()
{
	vShader.Get()->Release();
	inputElements.clear(); 
	inputElements.shrink_to_fit();
	inputLayout.Get()->Release(); 
	Shader::Release();

	return true;
}
#pragma endregion


#pragma region PixelShader methods
PixelShader::PixelShader(GraphicsEngine* gfx, LPCWSTR shaderFile) : Shader(gfx, shaderFile)
{

}

PixelShader::~PixelShader()
{

}

bool PixelShader::Init()
{
	Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob; 
	 
	if (FAILED(D3DReadFileToBlob(shaderFile, &shaderBlob))) 
	{
		return false;
	}

	if (FAILED(gfx->GetDevice()->CreatePixelShader(shaderBlob.Get()->GetBufferPointer(), shaderBlob.Get()->GetBufferSize(), nullptr, &pShader)))
	{
		return false;
	}
	 
	shaderBlob.Get()->Release(); 

	return true;
}

void PixelShader::BindToPipeline()
{
	gfx->GetDeviceContext()->PSSetShader(pShader.Get(), nullptr, 0u); 
}

bool PixelShader::Release()
{
	pShader.Get()->Release();
	Shader::Release();

	return true;
}
#pragma endregion