#pragma once
#include "PrimitiveObject.h"

class CapsuleObject : public PrimitiveObject
{
public:
	CapsuleObject(std::string name = "CapsuleObject", bool isRainbowed = false)
		: PrimitiveObject(name, EPrimitiveMeshTypes::Capsule, isRainbowed) {}
	~CapsuleObject() {}
};