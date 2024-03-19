#include "EntryPoint.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Render/SphereRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Light/DirectionalLight.h"
#include "Engine/Component/Transform.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Render/CubeRenderer.h"
#include "Engine/Math/CEuler.h"
#include "Engine/Math/CQuaternion.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Engine/Render/CapsuleRenderer.h"
#include "../TestCVector.h"


using namespace Engine;

EntryPoint::EntryPoint()
{
	// 光
	auto light = GlobalManager::GetInstance().globalLight;
	//light->GetTransform()->SetWorldPosition(CVector(1, 1, 1));
	light->GetTransform()->LookAt(CVector(-1, -1, -1) + light->GetTransform()->GetWorldPosition());
	//light->GetTransform()->SetLocalScale(CVector(0.1f, 0.1f, 1));
	light->SetIntensity(0.6f);
	//light->AddComponent<CubeRenderer>();

	CQuaternion qua = light->GetTransform()->GetWorldRotation();
	auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());

	// 摄像机
	GameObject* cameraObj = new GameObject();
	auto camera = cameraObj->AddComponent<Camera>();
	//cameraObj->GetTransform()->SetWorldPosition(CVector::Forward() * 5 + CVector::Left() * 1 + CVector::Up() * 1);
	cameraObj->GetTransform()->SetWorldPosition(CVector::Forward() * 5);
	cameraObj->GetTransform()->LookAt(CVector::Backward() + cameraObj->GetTransform()->GetWorldPosition());
}

void EntryPoint::Awake()
{
	// 作业1 -> TestCVector
	TestCVector();
}

void EntryPoint::Start()
{

	// 测试用球体
	GameObject* cube = new GameObject();
	auto renderer = cube->AddComponent<CubeRenderer>();
	renderer->GetMaterial()->SetUniform3f("objectColor", 0.0f, 1.0f, 1.0f);
}
