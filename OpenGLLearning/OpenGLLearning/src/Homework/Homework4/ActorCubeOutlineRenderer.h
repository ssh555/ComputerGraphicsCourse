#pragma once
#include "Engine/Render/CubeOutlineRenderer.h"

namespace Engine
{
	class GameObject;
}


class ActorCubeOutlineRenderer : public Engine::CubeOutlineRenderer
{
protected:
	virtual void Tick(float deltatime) override;
public:
	ActorCubeOutlineRenderer(Engine::GameObject* obj);


	float moveSpeed = 10.0f;
};

