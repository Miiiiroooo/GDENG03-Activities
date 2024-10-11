#pragma once
#include <Windows.h>
#include "../AComponent.h"


class GenericInputController : public AComponent
{
public:
	GenericInputController(std::string name);
	~GenericInputController();

	void ProcessInputs(WPARAM wParam, LPARAM lParam);


protected:
	WPARAM wParam;
	LPARAM lParam;
};