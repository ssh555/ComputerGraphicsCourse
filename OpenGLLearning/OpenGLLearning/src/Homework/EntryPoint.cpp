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
#include "Homework1/TestCVector.h"
#include "Homework1/Stage.h"


using namespace Engine;

EntryPoint::EntryPoint()
	: m_stage(nullptr), cameraObj(new GameObject())
{
	// ��
	auto light = GlobalManager::GetInstance().globalLight;
	//light->GetTransform()->SetWorldPosition(CVector(1, 1, 1));
	light->GetTransform()->LookAt(CVector(-1, -1, -1) + light->GetTransform()->GetWorldPosition());
	//light->GetTransform()->SetLocalScale(CVector(0.1f, 0.1f, 1));
	light->SetIntensity(0.6f);
	//light->AddComponent<CubeRenderer>();

	CQuaternion qua = light->GetTransform()->GetWorldRotation();
	auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());

	// �����
	auto camera = cameraObj->AddComponent<Camera>();
	//cameraObj->GetTransform()->SetWorldPosition(CVector::Forward() * 5 + CVector::Left() * 1 + CVector::Up() * 1);
	cameraObj->GetTransform()->SetWorldPosition(CVector::Forward() * 50 + CVector::Up() * 15);
	cameraObj->GetTransform()->LookAt(CVector::Backward() + CVector::Down() * 2 + cameraObj->GetTransform()->GetWorldPosition());
}

void EntryPoint::Awake()
{
	// ��ҵ1 -> TestCVector
	TestCVector();
}

void EntryPoint::Start()
{
	m_stage = new Stage();

}

EntryPoint::~EntryPoint()
{
	delete m_stage;
	delete cameraObj;
}
