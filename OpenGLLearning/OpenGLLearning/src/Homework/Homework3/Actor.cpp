#include "Actor.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Render/CubeOutlineRenderer.h"
#include "Engine/Component/Transform.h"
#include "Engine/Render/SphereRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Light/DirectionalLight.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Render/CubeRenderer.h"
#include "Engine/Math/CEuler.h"
#include "../Homework4/ActorCubeOutlineRenderer.h"

using namespace Engine;

Actor::Actor()
{
	RootEmpty = this;

	CubeOutline = new GameObject("OutLine");
	CubeOutline->SetParent(*RootEmpty);
	CubeOutline->GetTransform()->SetLocalPosition(CVector(0, 1.0f, 0.3f));
	CubeOutline->GetTransform()->SetLocalScale(CVector(1.0f, 1.7f, 0.6f));
	CubeOutline->AddComponent<ActorCubeOutlineRenderer>()->m_LineWidth = 2;
	CubeOutline->GetComponent<ActorCubeOutlineRenderer>()->SetEnable(false);
	//CubeOutline->SetActive(false);

	// 头
	Head = new GameObject("Head");
	Head->SetParent(*RootEmpty);
	Head->GetTransform()->SetLocalPosition(CVector(0, 1.5f, 0));
	Head->GetTransform()->SetLocalScale(CVector(0.6f, 0.6f, 0.6f));
	Head->AddComponent<SphereRenderer>()->SetMaterial(CreateMaterial(CVector(1.0f, 1.0f, 0.0f)));
	Head->GetComponent<MeshRenderer>()->bRayCast = true;

	// 面部 -> 前方
	Face = new GameObject("Face");
	Face->SetParent(*RootEmpty);
	Face->GetTransform()->SetLocalPosition(CVector(0, 1.5f, 0.3f));
	Face->GetTransform()->SetLocalScale(CVector(0.1f, 0.1f, 0.1f));
	Face->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(0.5f, 0.0f, 0.5f)));
	Face->GetComponent<MeshRenderer>()->bRayCast = true;

	// 躯干
	Torso = new GameObject("Torso");
	Torso->SetParent(*RootEmpty);
	Torso->GetTransform()->SetLocalPosition(CVector(0, 0.9f, 0));
	Torso->GetTransform()->SetLocalScale(CVector(0.6f, 0.6f, 0.6f));
	Torso->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(1.0f, 0, 0)));
	Torso->GetComponent<MeshRenderer>()->bRayCast = true;

	// 左臂
	LeftArm = new GameObject("LeftArm");
	LeftArm->SetParent(*RootEmpty);
	LeftArm->GetTransform()->SetLocalPosition(CVector(0.35f, 1.2f, 0));
	auto tmp = new GameObject();
	tmp->SetParent(*LeftArm);
	tmp->GetTransform()->SetLocalPosition(CVector(0, -0.2f, 0));
	tmp->GetTransform()->SetLocalScale(CVector(0.1f, 0.4f, 0.1f));
	tmp->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(0, 1.0f, 0)));
	tmp->GetComponent<MeshRenderer>()->bRayCast = true;

	// 右臂
	RightArm = new GameObject("RightArm");
	RightArm->SetParent(*RootEmpty);
	RightArm->GetTransform()->SetLocalPosition(CVector(-0.35f, 1.2f, 0));
	tmp = new GameObject();
	tmp->SetParent(*RightArm);
	tmp->GetTransform()->SetLocalPosition(CVector(0, -0.2f, 0));
	tmp->GetTransform()->SetLocalScale(CVector(0.1f, 0.4f, 0.1f));
	tmp->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(0, 1.0f, 0)));
	tmp->GetComponent<MeshRenderer>()->bRayCast = true;

	// 左腿
	LeftLeg = new GameObject("LeftLeg");
	LeftLeg->SetParent(*RootEmpty);
	LeftLeg->GetTransform()->SetLocalPosition(CVector(0.15f, 0.6f, 0));
	tmp = new GameObject();
	tmp->SetParent(*LeftLeg);
	tmp->GetTransform()->SetLocalPosition(CVector(0, -0.3f, 0));
	tmp->GetTransform()->SetLocalScale(CVector(0.1f, 0.6f, 0.1f));
	tmp->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(0, 0, 1)));
	tmp->GetComponent<MeshRenderer>()->bRayCast = true;

	// 右腿
	RightLeg = new GameObject("RightLeg");
	RightLeg->SetParent(*RootEmpty);
	RightLeg->GetTransform()->SetLocalPosition(CVector(-0.15f, 0.6f, 0));
	tmp = new GameObject();
	tmp->SetParent(*RightLeg);
	tmp->GetTransform()->SetLocalPosition(CVector(0, -0.3f, 0));
	tmp->GetTransform()->SetLocalScale(CVector(0.1f, 0.6f, 0.1f));
	tmp->AddComponent<CubeRenderer>()->SetMaterial(CreateMaterial(CVector(0, 0, 1)));
	tmp->GetComponent<MeshRenderer>()->bRayCast = true;
}

Actor::~Actor()
{
	//delete this->Head;
	//delete this->Face;
	//delete this->Torso;
	//delete this->LeftArm;
	//delete this->RightArm;
	//delete this->LeftLeg;
	//delete this->RightLeg;
	//if(RootEmpty)
	//	delete this->RootEmpty;
}

void Actor::PlayMoveAnimation(float deltaTime)
{
	// 增加当前时间
	currentTime += deltaTime; // 这里假设每次调用增加一个固定的时间步长，你可以根据需要调整

	// 设置周期和振幅
	float armSwingFrequency = 1.0f; // 手臂摆动频率
	float armSwingAmplitude = 0.3f; // 手臂摆动振幅
	float legSwingFrequency = 0.8f; // 腿摆动频率
	float legSwingAmplitude = 0.3f; // 腿摆动振幅

	// 计算摆动角度
	float armSwingAngle = armSwingAmplitude * sin(2 * PI * armSwingFrequency * currentTime) / PI * 180;
	float legSwingAngle = legSwingAmplitude * sin(2 * PI * legSwingFrequency * currentTime) / PI * 180;
	// 应用摆动角度到手臂和腿
	LeftArm->GetTransform()->SetLocalRotation(CEuler(0, armSwingAngle, 0).ToQuaternion());
	RightArm->GetTransform()->SetLocalRotation(CEuler(0, -armSwingAngle, 0).ToQuaternion());
	LeftLeg->GetTransform()->SetLocalRotation(CEuler(0, legSwingAngle, 0).ToQuaternion());
	RightLeg->GetTransform()->SetLocalRotation(CEuler(0, -legSwingAngle, 0).ToQuaternion());
}


Engine::Material* Actor::CreateMaterial(const CVector& color)
{
	auto mat = new Material();
	auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());
	mat->SetUniform3f(MeshRenderer::LIGHTDIRSTR, lightdir.x, lightdir.y, lightdir.z);
	auto lightcolor = GlobalManager::GetInstance().globalLight->GetLightColor() * GlobalManager::GetInstance().globalLight->GetIntensity();
	mat->SetUniform3f(MeshRenderer::LIGHTCOLOR, lightcolor.x, lightcolor.y, lightcolor.z);
	mat->SetUniform1f("ambientStrength", 0.6f);
	mat->SetUniform1f("specularStrength", 0.5);
	mat->SetUniform1f("shininess", 1);
	mat->SetUniform3f("objectColor", color.x, color.y, color.z);
	return mat;
}
