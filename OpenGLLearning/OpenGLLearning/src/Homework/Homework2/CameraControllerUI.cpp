#include "CameraControllerUI.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Camera/Camera.h"
#include "CameraController.h"
#include "imgui/imgui.h"
#include "Engine/Component/Transform.h"
#include "Engine/Math/CVector.h"


using namespace Engine;

CameraControllerUI::CameraControllerUI()
	: controller(GlobalManager::GetInstance().GetCamera()->GetComponent<CameraController>())
{
}

void CameraControllerUI::OnImGuiRender()
{
	auto pos = controller->transform->GetWorldPosition();
	ImGui::Text("%s: (%.2f, %.2f, %.2f)", "position", pos.x, pos.y,pos.z);
}
