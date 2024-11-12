#include "InspectorTab.h"
#include "HierarchyTab.h"
#include "../GameEngine/Managers/GameObjectManager.h"
#include "../WindowSystem/Keyboard.h"


InspectorTab::InspectorTab(HierarchyTab* hierarchy) : AUITab(EditorGUIManager::TabNames::INSPECTOR_TAB.data()), hierarchy(hierarchy)
{
    InitializeImGuiFlags();  
}

InspectorTab::~InspectorTab()
{

}

void InspectorTab::InitializeImGuiFlags()
{
    flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar; 
}

void InspectorTab::Render()
{
	if (hierarchy->GetSelectedObj() == nullptr) return;

    ImGui::Begin(name.c_str(), &isEnabled, flags); 

	AGameObject* selected = hierarchy->GetSelectedObj();
	Transform* t = selected->GetTransform();

	position[0] = t->LocalPosition.x;
	position[1] = t->LocalPosition.y;
	position[2] = t->LocalPosition.z;

	eulerAngle[0] = t->GetLocalEulerAngles().x;
	eulerAngle[1] = t->GetLocalEulerAngles().y;
	eulerAngle[2] = t->GetLocalEulerAngles().z;

	scale[0] = t->LocalScale.x;
	scale[1] = t->LocalScale.y;
	scale[2] = t->LocalScale.z;

	ImGui::Text(selected->Name.c_str());
	ImGui::DragFloat3("Position", position);
	ImGui::DragFloat3("Rotation", eulerAngle);
	ImGui::DragFloat3("Scale", scale);

	t->SetLocalPosition(Vector3(position[0], position[1], position[2]));
	t->Rotate(Vector3(eulerAngle[0], eulerAngle[1], eulerAngle[2]) - t->GetLocalEulerAngles());
	t->SetLocalScale(Vector3(scale[0], scale[1], scale[2]));

	ImGui::End();
}