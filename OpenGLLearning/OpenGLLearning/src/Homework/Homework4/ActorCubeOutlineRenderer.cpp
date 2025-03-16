#include "ActorCubeOutlineRenderer.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Component/Transform.h"
#include "Engine/Render/CubeOutlineRenderer.h"
#include <iostream>

using namespace Engine;


ActorCubeOutlineRenderer::ActorCubeOutlineRenderer(GameObject* obj) : CubeOutlineRenderer(obj)
{
	this->IsEnableTick = true;
}


void ActorCubeOutlineRenderer::Tick(float deltatime)
{
	Transform* tran = this->gameobject->GetRoot()->GetTransform();
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Left))
	{
		tran->Translate(tran->GetLeft() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Right))
	{
		tran->Translate(-tran->GetLeft() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Up))
	{
		tran->Translate(tran->GetForward() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Down))
	{
		tran->Translate(-tran->GetForward() * this->moveSpeed * deltatime);
	}
}
