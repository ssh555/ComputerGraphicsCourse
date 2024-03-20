#include "StageController.h"
#include <iostream>
#include "Engine/Component/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Render/CubeRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Math/CMath.h"

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
	this->m_plain->AddComponent<CubeRenderer>()->GetMaterial()->SetUniform3f("objectColor", 0.3f, 0.3f, 0.3f);
	this->m_plain->GetTransform()->SetLocalScale(CVector(100, 0.1, 100));
}

void StageController::CreateAStage()
{
	Material* mat = new Material();
	// ������̨�� -> λ����(0, 0, 0)
	auto centerStage = CreateCube();
	m_AStage.push_back(centerStage);
	auto centerTransform = centerStage->GetTransform();
	centerTransform->SetWorldPosition(this->gameobject->GetTransform()->GetWorldPosition() + CVector(0, 6, 0));
	centerTransform->SetLocalScale(CVector(1, 12, 1));
	centerStage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	// ƫ�ƣ���������̨����ת
	// 16 - 16cos(��/4*x/14)
	int angleratio = 3;
	int numStages = 14;
	Transform* last = centerTransform;

	int offsetAngle = 2;

	// ���14��
	for (int i = 1; i <= numStages; ++i)
	{
		auto stage = CreateCube();
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(CMath::PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / CMath::PI;
		transform->SetLocalPosition(CVector(-i, 6, posz)); // ������̨���λ��
		transform->SetLocalScale(CVector(1, 12, 1));
		//transform->RotateAround(centerTransform->GetLocalPosition(), centerTransform->GetUp(), -angle); // Χ��������̨����ת
		//transform->SetWorldRotation(CQuaternion::Identity());
		transform->Rotate(transform->GetUp(), angle);
		transform->SetWorldPosition(last->GetWorldPosition() + (last->GetForward() - last->GetLeft() - transform->GetForward() - transform->GetLeft()) * 0.5f);
		last = transform;
		stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	}

	last = centerTransform;
	// �Ҳ�14��
	for (int i = 1; i <= numStages; ++i)
	{
		auto stage = CreateCube();
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(CMath::PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / CMath::PI;
		transform->SetLocalPosition(CVector(i, 6, posz)); // ������̨���λ��
		transform->SetLocalScale(CVector(1, 12, 1));
		//transform->RotateAround(centerTransform->GetLocalPosition(), centerTransform->GetUp(), angle); // Χ��������̨����ת
		//transform->SetWorldRotation(CQuaternion::Identity());
		transform->Rotate(transform->GetUp(), -angle);
		transform->SetWorldPosition(last->GetWorldPosition() + (last->GetForward() + last->GetLeft() - transform->GetForward() + transform->GetLeft()) * 0.5f);
		last = transform;
		stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	}
}

void StageController::CreateBStage()
{
	Transform* centerTransform = this->gameobject->GetTransform();
	Material* mat = new Material();
	// B1
	// z : center pos z + 16.5 - z
	// x : center pos x - 4 + x
	for (int x = 0; x < 9; ++x)
	{
		for (int z = 0; z < 10; ++z)
		{
			auto stage = CreateCube();
			m_B1Stage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 4 + x, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - z)); // ������̨���λ��
			transform->SetLocalScale(CVector(1, 5, 1));
			stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
		}
	}
	// ��4��ʱ,x���Ҹ�ͻ��2��StageCube
	auto stage = CreateCube();
	m_B1Stage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // ������̨���λ��
	transform->SetLocalScale(CVector(1, 5, 1));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	stage = CreateCube();
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 6, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // ������̨���λ��
	transform->SetLocalScale(CVector(1, 5, 1));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	stage = CreateCube();
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // ������̨���λ��
	transform->SetLocalScale(CVector(1, 5, 1));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	stage = CreateCube();
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 6, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // ������̨���λ��
	transform->SetLocalScale(CVector(1, 5, 1));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	mat = new Material();
	// B2
	// z : center pos z + 6.5 - z
	// x : center pos x - 7 + x
	for (int x = 0; x < 15; ++x)
	{
		for (int z = 0; z < 4; ++z)
		{
			auto stage = CreateCube();
			m_B2Stage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 7 + x, -1.4f, centerTransform->GetWorldPosition().z + 6.5f - z)); // ������̨���λ��
			transform->SetLocalScale(CVector(1, 3, 1));
			stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
		}
	}

	mat = new Material();
	// BT-Other
	// 0.5*0.5�ߴ� -> һ������B��Cube = 4��BTCube
	// z : center pos z + 19 - 0.25 - z * 0.5
	// x : center pos x - count * 0.25 + 0.25 + x * 0.5 
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
			auto stage = CreateCube();
			m_BTStage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(posx, -2.4f, centerTransform->GetWorldPosition().z + 19 - 0.25f - z * 0.5f)); // ������̨���λ��
			transform->SetLocalScale(CVector(0.5f, 5, 0.5f));
			stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
		}
	}
}

void StageController::CreateCStage()
{
	Material* mat = new Material();
	Transform* centerTransform = this->gameobject->GetTransform();

	// z56�м� �պÿ���
	auto stage = CreateCube();
	m_CStage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z8 ǰ�� �պÿ���
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z9 �м� һ�뿿��
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 7.5f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z10 �м� һ�뿿��
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 8.5f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);

	//// z4 ǰ һ�뿿��
	//stage = CreateCube();
	//m_CStage.push_back(stage);
	//transform = stage->GetTransform();
	//transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 2.5f)); // ������̨���λ��
	//transform->SetLocalScale(CVector(3, 11, 0.5));
	// z56 �м� �պÿ���
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z8 �ϰ� �պÿ���
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z9 �м� һ�뿿��
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 8.0f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);
	// z10 �м� һ�뿿��
	stage = CreateCube();
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 9.0f)); // ������̨���λ��
	transform->SetLocalScale(CVector(3, 11, 0.5));
	stage->GetComponent<MeshRenderer>()->SetMaterial(mat);


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
	// ����A
	for (auto stage : m_AStage)
	{
		CVector color = m_AColor.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// ���� B1
	for (auto stage : m_B1Stage)
	{
		CVector color = m_B1Color.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// ���� B2
	for (auto stage : m_B2Stage)
	{
		CVector color = m_B2Color.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// ���� BT
	for (auto stage : m_BTStage)
	{
		CVector color = m_BTColor.color[index];
		stage->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	}
	// ���� C
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

Engine::GameObject* StageController::CreateCube()
{
	auto ret = new GameObject();
	ret->SetParent(*this->gameobject);
	ret->AddComponent<CubeRenderer>();
	return ret;
}
