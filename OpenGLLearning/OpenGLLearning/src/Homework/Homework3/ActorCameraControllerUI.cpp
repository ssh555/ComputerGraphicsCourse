#include "ActorCameraControllerUI.h"
#include "../Homework2/CameraController.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Camera/Camera.h"


using namespace Engine;

ActorCameraControllerUI::ActorCameraControllerUI() : CameraControllerUI()
{
	controller = GlobalManager::GetInstance().GetCamera(1)->GetComponent<CameraController>();
}
