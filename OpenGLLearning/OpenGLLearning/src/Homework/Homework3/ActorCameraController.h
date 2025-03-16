#pragma once
#include "../Homework2/CameraController.h"

namespace Engine
{
	class GameObject;
}

class ActorCameraController : public CameraController
{
	friend class Engine::GameObject;
private:
	ActorCameraController(Engine::GameObject* obj);
protected:
	virtual void Tick(float deltatime) override;


	virtual void Rotate(float deltatime) override;

};

