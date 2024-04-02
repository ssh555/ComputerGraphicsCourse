#pragma once
#include "Engine/Component/Component.h"

namespace Engine
{
	class GameObject;
	class Camera;
	class LineRenderer;
}

class CameraController : public Engine::Component
{
	friend class Engine::GameObject;
private:
	CameraController(Engine::GameObject* obj);
protected:
	virtual void Tick(float deltatime) override;


	virtual void LateTick(float deltatime) override;

	void Move();
	void Rotate();

protected:
	Engine::Camera* m_camera;

	Engine::LineRenderer* m_lineRenderer;

	float moveSpeed = 1.0f;
	float rotSpeed = 1.0f;

	void PrintCurrentState();

};

