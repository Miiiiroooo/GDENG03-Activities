#pragma once
#include"AUITab.h"


class DockSpace : public AUITab
{
public:
	DockSpace();
	~DockSpace();

	void Render() override;

protected:
	void InitializeImGuiFlags() override;


private:
	ImGuiDockNodeFlags dockSpaceFlags;
};