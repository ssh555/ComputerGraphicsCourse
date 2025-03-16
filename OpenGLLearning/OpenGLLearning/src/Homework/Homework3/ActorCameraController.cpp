#include "ActorCameraController.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Component/Transform.h"
#include "Actor.h"

using namespace Engine;

ActorCameraController::ActorCameraController(Engine::GameObject* obj) : CameraController(obj)
{

}

void ActorCameraController::Tick(float deltatime)
{
	auto mgr = GlobalManager::GetInstance().inputManager;

	// 欧拉角
	if (mgr->GetKeyDown(InputManager::Key::Num5))
	{
		if (this->EulerOrSelf == false)
		{
			euler = this->transform->GetWorldRotation().ToCEuler();
		}
		this->EulerOrSelf = true;
	}
	// 子坐标
	if (mgr->GetKeyDown(InputManager::Key::Num6))
	{
		this->EulerOrSelf = false;
	}

	if (mgr->GetKeyDown(InputManager::Key::Num8))
	{
		this->gameobject->SetActive(false);
		auto actor = static_cast<Actor*>(this->gameobject->GetRoot());
		//actor->camera->SetActive(true);
		actor->mainCamera->SetActive(true);
	}

}

void ActorCameraController::Rotate(float deltatime)
{
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::J))
	{
		if (EulerOrSelf)
		{
			euler.h += this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			this->transform->Rotate(this->transform->GetUp(), this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::L))
	{
		if (EulerOrSelf)
		{
			euler.h -= this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			// 子空间
			this->transform->Rotate(this->transform->GetUp(), -this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::K))
	{
		if (EulerOrSelf)
		{
			euler.p += this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			this->transform->Rotate(this->transform->GetLeft(), this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::I))
	{
		if (EulerOrSelf)
		{
			euler.p -= this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			this->transform->Rotate(this->transform->GetLeft(), -this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::U))
	{
		if (EulerOrSelf)
		{
			euler.b -= this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			this->transform->Rotate(this->transform->GetForward(), -this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::O))
	{
		if (EulerOrSelf)
		{
			euler.b += this->rotSpeed * deltatime;
			this->transform->SetLocalRotation(CQuaternion::Identity());
			this->transform->Rotate(CVector::Up(), euler.h);
			this->transform->Rotate(this->transform->GetLeft(), euler.p);
			this->transform->Rotate(this->transform->GetForward(), euler.b);
		}
		else
		{
			this->transform->Rotate(this->transform->GetForward(), this->rotSpeed * deltatime);
		}
	}

	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::RightBracket))
	{
		this->rotSpeed += 1;
	}
	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::LeftBracket))
	{
		this->rotSpeed -= 1;
	}

}
