#include "StageController.h"
#include <iostream>
#include "Engine/Component/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Render/CubeRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Math/CMath.h"
#include "Engine/Render/LineRenderer.h"
#include "Engine/Render/CubeOutlineRenderer.h"

StageController::StageController(GameObject* obj)
	: Component(obj)
{
	this->CreateStage();

	this->BindInput();

	this->InitStageColor();

	this->SwitchStageColor(false);
}

StageController::~StageController()
{
	delete m_plain;
}

void StageController::Tick(float deltatime)
{
	if (this->m_isRotating)
	{
		auto transform = this->gameobject->GetTransform();
		transform->Rotate(transform->GetUp(), m_rotRate * deltatime);
	}
}

void StageController::CreateStage()
{
	this->CreatePlain();
	this->CreateAStage();
	this->CreateBStage();
	this->CreateCStage();
}

void StageController::CreatePlain()
{
	this->m_plain = new GameObject();
	auto mat = CreateMat();
	mat->SetUniform3f("objectColor", 0.3f, 0.3f, 0.3f);
	this->m_plain->AddComponent<CubeRenderer>()->SetMaterial(mat);
	this->m_plain->GetTransform()->SetLocalScale(CVector(100, 0.1, 100));
}

void StageController::CreateAStage()
{
	auto mat = CreateMat();
	// 中心舞台块 -> 位置在(0, 0, 0)
	auto centerStage = CreateCube(mat);
	m_AStage.push_back(centerStage);
	auto centerTransform = centerStage->GetTransform();
	centerTransform->SetWorldPosition(this->gameobject->GetTransform()->GetWorldPosition() + CVector(0, 6, 0));
	centerTransform->SetLocalScale(CVector(1, 12, 1));

	// 偏移，绕中心舞台块旋转
	// 16 - 16cos(π/4*x/14)
	int angleratio = 3;
	int numStages = 14;
	Transform* last = centerTransform;

	int offsetAngle = 2;

	// 左侧14个
	for (int i = 1; i <= numStages; ++i)
	{
		auto stage = CreateCube(mat);
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(CMath::PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / CMath::PI;
		transform->SetLocalPosition(CVector(-i, 6, posz)); // 设置舞台块的位置
		transform->SetLocalScale(CVector(1, 12, 1));
		//transform->RotateAround(centerTransform->GetLocalPosition(), centerTransform->GetUp(), -angle); // 围绕中心舞台块旋转
		//transform->SetWorldRotation(CQuaternion::Identity());
		transform->Rotate(transform->GetUp(), angle);
		transform->SetWorldPosition(last->GetWorldPosition() + (last->GetForward() - last->GetLeft() - transform->GetForward() - transform->GetLeft()) * 0.5f);
		last = transform;
	}

	last = centerTransform;
	// 右侧14个
	for (int i = 1; i <= numStages; ++i)
	{
		auto stage = CreateCube(mat);
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(CMath::PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / CMath::PI;
		transform->SetLocalPosition(CVector(i, 6, posz)); // 设置舞台块的位置
		transform->SetLocalScale(CVector(1, 12, 1));
		//transform->RotateAround(centerTransform->GetLocalPosition(), centerTransform->GetUp(), angle); // 围绕中心舞台块旋转
		//transform->SetWorldRotation(CQuaternion::Identity());
		transform->Rotate(transform->GetUp(), -angle);
		transform->SetWorldPosition(last->GetWorldPosition() + (last->GetForward() + last->GetLeft() - transform->GetForward() + transform->GetLeft()) * 0.5f);
		last = transform;
	}
}

void StageController::CreateBStage()
{
	auto mat = CreateMat();
	Transform* centerTransform = this->gameobject->GetTransform();
	// B1
	// z : center pos z + 16.5 - z
	// x : center pos x - 4 + x
	for (int x = 0; x < 9; ++x)
	{
		for (int z = 0; z < 10; ++z)
		{
			auto stage = CreateCube(mat);
			m_B1Stage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 4 + x, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - z)); // 设置舞台块的位置
			transform->SetLocalScale(CVector(1, 5, 1));
		}
	}
	// 第4行时,x左右各突出2个StageCube
	auto stage = CreateCube(mat);
	m_B1Stage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	stage = CreateCube(mat);
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 6, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	stage = CreateCube(mat);
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	stage = CreateCube(mat);
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 6, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	// B2
	// z : center pos z + 6.5 - z
	// x : center pos x - 7 + x
	mat = CreateMat();
	for (int x = 0; x < 15; ++x)
	{
		for (int z = 0; z < 4; ++z)
		{
			auto stage = CreateCube(mat);
			m_B2Stage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 7 + x, -1.4f, centerTransform->GetWorldPosition().z + 6.5f - z)); // 设置舞台块的位置
			transform->SetLocalScale(CVector(1, 3, 1));
		}
	}

	// BT-Other
	// 0.5*0.5尺寸 -> 一个正常B区Cube = 4个BTCube
	// z : center pos z + 19 - 0.25 - z * 0.5
	// x : center pos x - count * 0.25 + 0.25 + x * 0.5 
	mat = CreateMat();
	float bounds[19] = { -1,-1, 4.5f,4.5f,4.5f,6.5f,4.5f,4.5f,4.5f ,4.5f,4.5f,4.5f ,7.5f ,7.5f ,7.5f ,7.5f,-1,-1,-1 };
	int counts[37] = { 6,8,10,12,62,62,58 ,58 ,58 ,58 ,58 ,58 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56 ,56,54,54,52,50,48,46,43,40 };
	for (int z = 0; z < 37; ++z)
	{
		for (int x = 0; x < counts[z]; ++x)
		{
			float posx = centerTransform->GetWorldPosition().x - counts[z] * 0.25f + 0.25 + x * 0.5;
			if (bounds[(int)((float)z * 0.5f)] >= abs(posx))
			{
				continue;
			}
			auto stage = CreateCube(mat);
			m_BTStage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(posx, -2.4f, centerTransform->GetWorldPosition().z + 19 - 0.25f - z * 0.5f)); // 设置舞台块的位置
			transform->SetLocalScale(CVector(0.5f, 5, 0.5f));
		}
	}
}

void StageController::CreateCStage()
{
	auto mat = CreateMat();
	Transform* centerTransform = this->gameobject->GetTransform();

	// z56中间 刚好靠边
	auto stage = CreateCube(mat);
	m_CStage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z8 前半 刚好靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z9 中间 一半靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 7.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z10 中间 一半靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 8.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));

	//// z4 前 一半靠边
	//stage = CreateCube();
	//m_CStage.push_back(stage);
	//transform = stage->GetTransform();
	//transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 2.5f)); // 设置舞台块的位置
	//transform->SetLocalScale(CVector(3, 11, 0.5));
	// z56 中间 刚好靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z8 上半 刚好靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z9 中间 一半靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 8.0f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z10 中间 一半靠边
	stage = CreateCube(mat);
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 9.0f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));


}

void StageController::BindInput()
{
	GlobalManager::GetInstance().inputManager->RegisterKeyCallback(InputManager::Key::Num1, [this](InputManager::Key key, InputManager::KeyAction action)
		{
			if (action == InputManager::KeyAction::Press)
			{
				this->SwitchStageColor(!m_colorState);
			}
		});
	GlobalManager::GetInstance().inputManager->RegisterKeyCallback(InputManager::Key::Num2, [this](InputManager::Key key, InputManager::KeyAction action)
		{
			if (action == InputManager::KeyAction::Press)
			{
				this->m_isRotating = !this->m_isRotating;
			}
		});
}

void StageController::SwitchStageColor(bool colorState)
{
	m_colorState = colorState;
	int index = (int)m_colorState;
	// 更换A
	for (auto stage : m_AStage)
	{
		CVector color = m_AColor.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// 更换 B1
	for (auto stage : m_B1Stage)
	{
		CVector color = m_B1Color.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// 更换 B2
	for (auto stage : m_B2Stage)
	{
		CVector color = m_B2Color.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// 更换 BT
	for (auto stage : m_BTStage)
	{
		CVector color = m_BTColor.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// 更换 C
	for (auto stage : m_CStage)
	{
		CVector color = m_CColor.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
}

void StageController::InitStageColor()
{
	this->m_AColor.color[0].SetVec(0, 0, 1);
	this->m_AColor.color[1].SetVec(0, 1, 1);

	this->m_B1Color.color[0].SetVec(0, 0, 1);
	this->m_B1Color.color[1].SetVec(1, 0, 0);

	this->m_B2Color.color[0].SetVec(0, 0.4, 1);
	this->m_B2Color.color[1].SetVec(1, 1, 0);

	this->m_BTColor.color[0].SetVec(0, 1, 1);
	this->m_BTColor.color[1].SetVec(1, 0, 1);

	this->m_CColor.color[0].SetVec(0, 1, 0.4);
	this->m_CColor.color[1].SetVec(1, 0.5, 0.5);
}

Engine::GameObject* StageController::CreateCube(Material* mat)
{
	auto ret = new GameObject();
	ret->SetParent(*this->gameobject);
	ret->AddComponent<CubeRenderer>()->SetMaterial(mat);
	ret->AddComponent<CubeOutlineRenderer>();
	return ret;
}

Engine::Material* StageController::CreateMat()
{
	auto mat = new Material();
	auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());
	mat->SetUniform3f(MeshRenderer::LIGHTDIRSTR, lightdir.x, lightdir.y, lightdir.z);
	auto color = GlobalManager::GetInstance().globalLight->GetLightColor() * GlobalManager::GetInstance().globalLight->GetIntensity();
	mat->SetUniform3f(MeshRenderer::LIGHTCOLOR, color.x, color.y, color.z);
	mat->SetUniform1f("ambientStrength", 0.6f);
	mat->SetUniform1f("specularStrength", 0.5);
	mat->SetUniform1f("shininess", 1);
	return mat;
}
