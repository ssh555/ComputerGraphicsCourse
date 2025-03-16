#include "ActorController.h"
#include "Actor.h"
#include "Engine/Math/CQuaternion.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/Transform.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Camera/Camera.h"
#include "ActorCameraController.h"
#include "ActorCameraControllerUI.h"
#include "Engine/Render/LineRenderer.h"

ActorController::ActorController(GameObject* obj) : Component(obj),
	sphereCenter(0, 0, 10.5f),
	minRadius(1.5f),
	maxRadius(5)
{
	currentRadius = minRadius + 0.1f;

	auto camera = new GameObject("ActorCamera");
	camera->AddComponent<Camera>()->SetEnable(true);
	camera->AddComponent<ActorCameraController>();
	camera->SetActive(false);
	GlobalManager::GetInstance().testMenu->RegisterTest<ActorCameraControllerUI>("ActorCameraController");

	for (int i = 0; i < 12; ++i)
	{
		auto actor = new Actor();
		actor->Name = "Root";
		actors[i] = actor;
		CQuaternion q;
		actor->RootEmpty->GetTransform()->SetWorldPosition(GetSpherePoint(sphereCenter, currentRadius, i * 30 / 180.0f * PI, q));
		actor->RootEmpty->GetTransform()->SetWorldRotation(q);
		actor->camera = camera;
	}

	//GlobalManager::GetInstance().inputManager->RegisterKeyCallback(InputManager::Key::Num1, Move);
}

ActorController::~ActorController()
{
	for (int i = 0; i < 12; ++i)
	{
		delete actors[i];
	}
}

void ActorController::Move(float deltatime)
{
	// 位于MinRadius|MaxRadius: 旋转
	if (currentRadius <= minRadius || currentRadius >= maxRadius)
	{
		if (!IsRotating)
		{
			MoveForward = !MoveForward;
			currentRadius = MoveForward ? minRadius : maxRadius;
			IsRotating = true;
		}
		float d = deltatime * rotspeed;
		rot += deltatime * rotspeed;
		if (rot >= 180)
		{
			IsRotating = false;
			rot = 0;
		}
		for (int i = 0; i < 12; ++i)
		{
			auto actor = actors[i];
			actor->RootEmpty->GetTransform()->Rotate(CVector::Up(), d);
			actor->PlayMoveAnimation(deltatime);
		}
	}
	if (IsRotating)
	{
		return;
	}

	// 位于中间: 移动
	currentRadius += deltatime * movespeed * (MoveForward ? 1 : -1);
	for (int i = 0; i < 12; ++i)
	{
		auto actor = actors[i];
		// 移动
		CQuaternion q;
		actor->RootEmpty->GetTransform()->SetWorldPosition(GetSpherePoint(sphereCenter, currentRadius, i * 30 / 180.0f * PI, q));
		//actor->RootEmpty->GetTransform()->SetWorldRotation(q);
		// 播放动画
		actor->PlayMoveAnimation(deltatime);
	}
}

Engine::CVector ActorController::GetSpherePoint(CVector center, float radius, float angle, CQuaternion& lookatout)
{
	CVector forward(0, 0, radius);
	lookatout = CQuaternion::quatFromAxisAngle(CVector::Up(), angle);
	return center + lookatout * forward;
}

void ActorController::Tick(float deltatime)
{
	auto mgr = GlobalManager::GetInstance().inputManager;

	if (mgr->GetKeyDown(InputManager::Key::Num7))
	{
		IsMove = !IsMove;
	}

	if (IsMove)
	{
		Move(deltatime);
	}
}
