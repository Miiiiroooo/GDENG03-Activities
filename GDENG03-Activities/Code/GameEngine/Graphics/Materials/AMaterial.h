#pragma once
#include "DirectXClasses/Shader.h"
#include "../IRenderable.h"


// due to the complexity of serialization of data types, materials in this project are HARD-CODED
class AMaterial : public IRenderable
{
public:
	AMaterial(LPCWSTR shaderType) : shaderType(shaderType) {}
	~AMaterial() {};

	LPCWSTR GetShaderType() { return shaderType; };


protected:
	LPCWSTR shaderType;
};