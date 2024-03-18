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


using namespace Engine;

EntryPoint::EntryPoint()
{
	// 光
	auto light = GlobalManager::GetInstance().globalLight;
	light->GetTransform()->LookAt(CVector(-1, -1, -1));
	light->SetIntensity(1);
	
	// 摄像机
	GameObject* cameraObj = new GameObject();
	auto camera = cameraObj->AddComponent<Camera>();
	cameraObj->GetTransform()->SetWorldPosition(CVector::Forward() * 5 + CVector::Left() * 1 + CVector::Up() * 1);
	cameraObj->GetTransform()->LookAt(CVector::Backward() + cameraObj->GetTransform()->GetWorldPosition());
}

void EntryPoint::Awake()
{
	// 测试用球体
	GameObject* cube = new GameObject();
	auto renderer = cube->AddComponent<CubeRenderer>();
	renderer->GetMaterial()->SetUniform3f("objectColor", 0.0f, 1.0f, 1.0f);
}

void EntryPoint::Start()
{

}
