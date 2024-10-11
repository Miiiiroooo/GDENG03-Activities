#include "GenericInputController.h"

GenericInputController::GenericInputController(std::string name) : AComponent(name, EComponentTypes::Input)
{

}

GenericInputController::~GenericInputController()
{

}

void GenericInputController::ProcessInputs(WPARAM wParam, LPARAM lParam)
{
	this->wParam = wParam;
	this->lParam = lParam;
}