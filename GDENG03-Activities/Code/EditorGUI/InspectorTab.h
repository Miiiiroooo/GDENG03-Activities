#pragma once
#include "AUITab.h"

class HierarchyTab;

class InspectorTab : public AUITab
{
public:
	InspectorTab(HierarchyTab* hierarchy);
	~InspectorTab();

	void Render() override;

protected:
	void InitializeImGuiFlags() override;


private:
	HierarchyTab* hierarchy;

	float position[3];
	float eulerAngle[3];
	float scale[3];
};

