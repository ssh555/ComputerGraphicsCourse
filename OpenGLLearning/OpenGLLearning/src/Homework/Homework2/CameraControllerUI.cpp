#include "CameraControllerUI.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Camera/Camera.h"
#include "CameraController.h"
#include "imgui/imgui.h"
#include "Engine/Component/Transform.h"
#include "Engine/Math/CVector.h"
#include "Engine/Math/CQuaternion.h"


using namespace Engine;

CameraControllerUI::CameraControllerUI()
	: controller(GlobalManager::GetInstance().GetCamera()->GetComponent<CameraController>())
{
}

void CameraControllerUI::OnImGuiRender()
{
	// 显示当前视点位置
	auto pos = controller->transform->GetWorldPosition();
	if (ImGui::DragFloat3("position", pos))
	{
		controller->transform->SetWorldPosition(pos);
	}
	//auto localpos = controller->transform->GetLocalPosition();
	//ImGui::Text("%s: (%.2f, %.2f, %.2f)", "localposition", localpos.x, localpos.y, localpos.z);

	if(!(this->rot.ToQuaternion() == controller->transform->GetWorldRotation()))
		this->rot = controller->transform->GetWorldRotation().ToCEuler();

	// 显示欧拉角
	CVector rotation(rot.p, rot.h, rot.b);
	if (ImGui::DragFloat3("rotation", rotation))
	{
		rot.p = rotation.x;
		rot.h = rotation.y;
		rot.b = rotation.z;
		controller->transform->SetWorldRotation(CQuaternion::Identity());
		controller->transform->Rotate(CVector::Up(), rotation.y);
		controller->transform->Rotate(controller->transform->GetLeft(), rotation.x);
		controller->transform->Rotate(controller->transform->GetForward(), rotation.z);
	}

	// 显示四元数
	auto quat = this->rot.ToQuaternion();
	ImGui::Text("%s: (%.2f, %.2f, %.2f, %.2f)", "quaternion", quat.w, quat.x, quat.y, quat.z);

	// 显示前方向量
	auto forward = controller->transform->GetForward();
	ImGui::Text("%s: (%.2f, %.2f, %.2f)", "forward", forward.x, forward.y, forward.z);
	// 显示上方向量
	auto up = controller->transform->GetUp();
	ImGui::Text("%s: (%.2f, %.2f, %.2f)", "upward", up.x, up.y, up.z);


	ImGui::DragFloat("move speed", &controller->moveSpeed);

	ImGui::DragFloat("rotate speed", &controller->rotSpeed);

	ImGui::DragFloat("select rotate speed", &controller->selectRotSpeed);

}
