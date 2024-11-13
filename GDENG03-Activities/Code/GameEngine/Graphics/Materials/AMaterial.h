#pragma once
#include "DirectXClasses/Shader.h"
#include "../IRenderable.h"


// materials  might require some serialization and other more modules; so for now materials in this project are HARD-CODED into classes
class AMaterial : public IRenderable
{
public:
	AMaterial(LPCWSTR shaderType) : shaderType(shaderType) {}
	~AMaterial() {};

	LPCWSTR GetShaderType() { return shaderType; };


protected:
	LPCWSTR shaderType;
};