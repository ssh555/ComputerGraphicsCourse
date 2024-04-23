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
	auto pos = controller->transform->GetWorldPosition();
	if (ImGui::DragFloat3("position", pos))
	{
		controller->transform->SetWorldPosition(pos);

	}

	ImGui::DragFloat("move speed", &controller->moveSpeed);

	//ImGui::DragFloat4("q1", this->rot.ToQuaternion());
	//ImGui::DragFloat4("q2", controller->transform->GetWorldRotation());
	if(!(this->rot.ToQuaternion() == controller->transform->GetWorldRotation()))
		this->rot = controller->transform->GetWorldRotation().ToCEuler();

	CVector rotation(rot.p, rot.h, rot.b);
	//cout << "QWQ " << rotation.x << " " << rotation.y << " " << rotation.z << endl;
	if (ImGui::DragFloat3("rotation", rotation))
	{
		rot.p = rotation.x;
		rot.h = rotation.y;
		rot.b = rotation.z;
		//controller->transform->SetWorldRotation(rot.ToQuaternion());
		//cout << rotation.x << " " << rotation.y << " " << rotation.z << endl;
		controller->transform->SetWorldRotation(CQuaternion::Identity());
		controller->transform->Rotate(CVector::Up(), rotation.y);
		controller->transform->Rotate(controller->transform->GetLeft(), rotation.x);
		controller->transform->Rotate(controller->transform->GetForward(), rotation.z);
	}

	ImGui::DragFloat("rotate speed", &controller->rotSpeed);

	ImGui::DragFloat("select rotate speed", &controller->selectRotSpeed);

}
