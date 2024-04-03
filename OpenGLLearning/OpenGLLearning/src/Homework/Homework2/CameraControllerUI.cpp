#include "CameraControllerUI.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Camera/Camera.h"
#include "CameraController.h"
#include "imgui/imgui.h"
#include "Engine/Component/Transform.h"
#include "Engine/Math/CVector.h"
#include "Engine/Math/CEuler.h"


using namespace Engine;

CameraControllerUI::CameraControllerUI()
	: controller(GlobalManager::GetInstance().GetCamera()->GetComponent<CameraController>())
{
}

void CameraControllerUI::OnImGuiRender()
{
	auto pos = controller->transform->GetWorldPosition();
	if (ImGui::DragFloat3("position", pos))
	{
		controller->transform->SetWorldPosition(pos);

	}

	ImGui::DragFloat("move speed", &controller->moveSpeed);

	auto rot = controller->transform->GetWorldRotation().ToCEuler();
	CVector rotation(rot.p, rot.h, rot.b);
	if (ImGui::DragFloat3("rotation", rotation))
	{
		rot.p = rotation.y;
		rot.h = rotation.x;
		rot.b = rotation.z;
		controller->transform->SetWorldRotation(rot.ToQuaternion());
	}

	ImGui::DragFloat("rotate speed", &controller->rotSpeed);

	ImGui::DragFloat("select rotate speed", &controller->selectRotSpeed);

}
