#pragma once
#include <imgui.h>
#include <imgui_impl_dx11.h> 
#include <imgui_impl_win32.h> 
#include <string>
#include "EditorGUIManager.h"
#include "GameEngine/Graphics/IRenderable.h"


class AUITab : public IRenderable
{
public:
	AUITab(std::string name);
	~AUITab();

	std::string GetName();
	void SetName(std::string newName);
	__declspec(property(get = GetName, put = SetName)) std::string Name;

	bool IsEnabled();
	void SetEnabled(bool flag); 
	__declspec(property(get = IsEnabled, put = SetEnabled)) bool Enabled; 

protected:
	virtual void InitializeImGuiFlags() {};


protected:
	std::string name;
	bool isEnabled;
	ImGuiWindowFlags flags;
};