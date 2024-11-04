#pragma once
#include <vector>
#include "AUITab.h"
#include "GameEngine/GameObjects/AGameObject.h"


class HierarchyTab : public AUITab
{
public:
	HierarchyTab();
	~HierarchyTab(); 

	void Render() override;

protected:
	void InitializeImGuiFlags() override;

private:
	void PrintObject(AGameObject* obj);


private:
	AGameObject* selectedObject;
};