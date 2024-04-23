#pragma once
#include "Engine/Component/Component.h"
#include "Engine/Math/CVector.h"

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

	void Move(float deltatime);
	virtual void Rotate(float deltatime);

protected:
	Engine::Camera* m_camera;

	Engine::LineRenderer* m_lineRenderer;

	void SelectGameObject(Engine::GameObject* obj);


public:
	float moveSpeed = 60.0f;
	float rotSpeed = 30.0f;
	float selectRotSpeed = 15.0f;

	Engine::GameObject* CurSelected = nullptr;
	Engine::CVector hitPoint;
	Engine::CVector SelectedPoint;
	float hitT;


};

