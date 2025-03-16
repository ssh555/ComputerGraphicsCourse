#pragma once
#include "Engine/Math/CVector.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Component/Component.h"

using namespace Engine;

class Actor;
namespace Engine
{
	class GameObject;
	class Component;
};

class ActorController : public Engine::Component
{
public:
	ActorController(GameObject* obj);
	~ActorController();

public:
	void Move(float deltatime);

public:
	// 12个演员
	Actor* actors[12];

	// 默认不移动
	bool IsMove = false;

	// 圆心
	CVector sphereCenter;
	// 当前半径
	float currentRadius;
	// 最小半径
	float minRadius;
	// 最大半径
	float maxRadius;
	float movespeed = 1;
	float rotspeed = 60;

	// true: min -> max
	// false: max -> min
	bool MoveForward = true;
	bool IsRotating = false;
	float rot = 0;

	// 弧度
	CVector GetSpherePoint(CVector center, float radius, float angle, CQuaternion& lookatout);
protected:
	virtual void Tick(float deltatime) override;

};

