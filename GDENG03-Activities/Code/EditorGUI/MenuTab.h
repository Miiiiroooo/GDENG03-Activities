#pragma once
#include "AUITab.h"

class MenuTab : public AUITab
{
public:
	MenuTab();
	~MenuTab();

	void Render() override;


private:
	void RenderFilesMenu();
	void RenderTabsMenu();
	void RenderToolsMenu();
	void RenderAboutMenu();
};