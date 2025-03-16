#pragma once
#include "Engine/Math/CVector.h"
#include "Engine/GameObject/GameObject.h"
using namespace Engine;

namespace Engine
{
	class GameObject;
	class Material;
}

class Actor : public GameObject
{
public:
	Actor();
	~Actor();

public:
	// 根物体，空物体
	GameObject* RootEmpty;
	// 头
	GameObject* Head;
	// 左臂
	GameObject* LeftArm;
	// 右臂
	GameObject* RightArm;
	// 左腿
	GameObject* LeftLeg;
	// 右腿
	GameObject* RightLeg;
	// 躯干
	GameObject* Torso;
	// 面部 : 主要用于区分哪一面是正面
	GameObject* Face;
	// 外部线框
	GameObject* CubeOutline;

	GameObject* camera;

	GameObject* mainCamera;

	float currentTime = 0; // 当前时间
	// 播放移动动画
	void PlayMoveAnimation(float deltaTime);

private: 
	Material* CreateMaterial(const CVector& color);
};

