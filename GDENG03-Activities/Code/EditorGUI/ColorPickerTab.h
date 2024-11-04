#pragma once
#include "AUITab.h"


class ColorPickerTab : public AUITab
{
public:
	ColorPickerTab();
	~ColorPickerTab();

	void Render() override;

protected:
	void InitializeImGuiFlags() override;


private:
	ImVec4 color;
};