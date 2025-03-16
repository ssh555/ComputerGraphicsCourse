#pragma once
#include "Engine/Component/Component.h"
#include "Engine/Math/CVector.h"
#include "Engine/Math/CEuler.h"

namespace Engine
{
	class GameObject;
	class Camera;
	class LineRenderer;
}

class CameraController : public Engine::Component
{
	friend class Engine::GameObject;
protected:
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

	// true : 使用欧拉角旋转
	// false : 使用子坐标系旋转
	bool EulerOrSelf = true;
	Engine::CEuler euler;


public:
	float moveSpeed = 60.0f;
	float rotSpeed = 30.0f;
	float selectRotSpeed = 15.0f;

	//CEuler euler;

	Engine::GameObject* CurSelected = nullptr;
	Engine::CVector hitPoint;
	Engine::CVector SelectedPoint;
	float hitT;


};

