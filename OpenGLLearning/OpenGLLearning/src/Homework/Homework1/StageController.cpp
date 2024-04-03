#include "StageController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Engine/Component/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Render/CubeRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Math/CMath.h"
#include "Engine/Render/LineRenderer.h"
#include "Engine/Render/CubeOutlineRenderer.h"
#include <iosfwd>

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

	if (this->m_enableBMotion)
	{
		this->BStageMotion(deltatime);
	}

	if (this->m_enableCMotion)
	{
		this->CStageMotion(deltatime);
	}

	auto mgr = GlobalManager::GetInstance().inputManager;
	// 保存
	if (mgr->GetKeyDown(InputManager::Key::F2))
	{
		this->SaveData(SLPATH);
	}
	// 读取
	if (mgr->GetKeyDown(InputManager::Key::F3))
	{
		this->LoadData(SLPATH);
	}
}

void StageController::CreateStage()
{
	this->CreatePlain();
	this->CreateAStage();
	this->CreateBStage();
	this->CreateCStage();
	SaveData(INITPATH);
}

void StageController::CreatePlain()
{
	this->m_plain = new GameObject("Plane");

	//this->m_plain->AddComponent<CubeOutlineRenderer>()->Color = CVector(1.0f, 0.0f, 0.0f);
	//this->m_plain->GetComponent<CubeOutlineRenderer>()->SetEnable(true);

	auto mat = CreateMat();
	mat->SetUniform3f("objectColor", 0.3f, 0.3f, 0.3f);
	this->m_plain->AddComponent<CubeRenderer>()->SetMaterial(mat);
	this->m_plain->GetTransform()->SetLocalScale(CVector(100, 0.1f, 100));
}

void StageController::CreateAStage()
{
	auto mat = CreateMat();
	// 中心舞台块 -> 位置在(0, 0, 0)
	auto centerStage = CreateCube(mat, "A-15");
	//centerStage->GetComponent<MeshRenderer>()->bRayCast = true;
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
		auto stage = CreateCube(mat, "A-" + std::to_string(i));
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / PI;
		transform->SetLocalPosition(CVector((float)-i, 6, posz)); // 设置舞台块的位置
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
		auto stage = CreateCube(mat, "A-" + std::to_string(15 + i));
		m_AStage.push_back(stage);
		auto transform = stage->GetTransform();
		float posz = (16 - 16 * cos(PI / angleratio * i / 14));
		float angle = atan(posz / i) * 180 / PI;
		transform->SetLocalPosition(CVector((float)i, 6, posz)); // 设置舞台块的位置
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
			auto stage = CreateCube(mat, "B1-" + std::to_string(z + 1) + "_" + std::to_string(x + 1));
			m_B1Stage.push_back(stage);
			auto transform = stage->GetTransform();
			transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 4 + x, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - z)); // 设置舞台块的位置
			transform->SetLocalScale(CVector(1, 5, 1));
		}
	}
	// 第4行时,x左右各突出2个StageCube
	// B1-L2
	auto stage = CreateCube(mat, "B1-L2");
	m_B1Stage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	// B1-L1
	stage = CreateCube(mat, "B1-L1");
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 6, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	// B1-R2
	stage = CreateCube(mat, "B1-R2");
	m_B1Stage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 5, -2.4f, centerTransform->GetWorldPosition().z + 16.5f - 3)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(1, 5, 1));
	// B1-R1
	stage = CreateCube(mat, "B1-R1");
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
			auto stage = CreateCube(mat, "B2-" + std::to_string(z + 1) + "_" + std::to_string(x + 1));
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
			float posx = centerTransform->GetWorldPosition().x - counts[z] * 0.25f + 0.25f + x * 0.5f;
			if (bounds[(int)((float)z * 0.5f)] >= abs(posx))
			{
				continue;
			}
			auto stage = CreateCube(mat, "BT");

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
	auto stage = CreateCube(mat, "C-1_1");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	auto transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z8 前半 刚好靠边
	stage = CreateCube(mat, "C-1_2");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z9 中间 一半靠边
	stage = CreateCube(mat, "C-1_3");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x - 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 7.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z10 中间 一半靠边
	stage = CreateCube(mat, "C-1_4");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
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
	stage = CreateCube(mat, "C-2_1");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 4.5f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z8 上半 刚好靠边
	stage = CreateCube(mat, "C-2_2");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 15.5f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 6.75f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z9 中间 一半靠边
	stage = CreateCube(mat, "C-2_3");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
	m_CStage.push_back(stage);
	transform = stage->GetTransform();
	transform->SetLocalPosition(CVector(centerTransform->GetWorldPosition().x + 14.0f, 5.5f, centerTransform->GetWorldPosition().z + 16.5f - 8.0f)); // 设置舞台块的位置
	transform->SetLocalScale(CVector(3, 11, 0.5));
	// z10 中间 一半靠边
	stage = CreateCube(mat, "C-2_4");
	stage->GetComponent<MeshRenderer>()->bRayCast = true;
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
	GlobalManager::GetInstance().inputManager->RegisterKeyCallback(InputManager::Key::Num3, [this](InputManager::Key key, InputManager::KeyAction action)
		{
			if (action == InputManager::KeyAction::Press)
			{
				this->m_enableBMotion = !this->m_enableBMotion;
				if (this->m_enableBMotion)
				{
					LoadData(INITPATH, true, false, true);
					m_BTime = 0;
				}
			}
		});
	GlobalManager::GetInstance().inputManager->RegisterKeyCallback(InputManager::Key::Num4, [this](InputManager::Key key, InputManager::KeyAction action)
		{
			if (action == InputManager::KeyAction::Press)
			{
				this->m_enableCMotion = !this->m_enableCMotion;
				if (this->m_enableCMotion)
				{
					LoadData(INITPATH, true, true, false);
					m_CTime = 0;
				}
			}
		});
}

void StageController::SwitchStageColor(bool colorState)
{
	m_colorState = colorState;
	int index = (int)m_colorState;
	// 更换A
	CVector color = m_AColor.color[index];
	m_AStage[0]->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	// 更换 B1
	color = m_B1Color.color[index];
	m_B1Stage[0]->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	// 更换 B2
	color = m_B2Color.color[index];
	m_B2Stage[0]->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	// 更换 BT
	color = m_BTColor.color[index];
	m_BTStage[0]->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
	// 更换 C
	color = m_CColor.color[index];
	m_CStage[0]->GetComponent<MeshRenderer>()->GetMaterial()->SetUniform3f("objectColor", color.x, color.y, color.z);
}

void StageController::InitStageColor()
{
	this->m_AColor.color[0].SetVec(0, 0, 1);
	this->m_AColor.color[1].SetVec(0, 1, 1);

	this->m_B1Color.color[0].SetVec(0, 0, 1);
	this->m_B1Color.color[1].SetVec(1, 0, 0);

	this->m_B2Color.color[0].SetVec(0, 0.4f, 1);
	this->m_B2Color.color[1].SetVec(1, 1, 0);

	this->m_BTColor.color[0].SetVec(0, 1, 1);
	this->m_BTColor.color[1].SetVec(1, 0, 1);

	this->m_CColor.color[0].SetVec(0, 1, 0.4f);
	this->m_CColor.color[1].SetVec(1, 0.5f, 0.5f);
}

Engine::GameObject* StageController::CreateCube(Material* mat, const string& name)
{
	auto ret = new GameObject(name);
	ret->SetParent(*this->gameobject);
	ret->AddComponent<CubeRenderer>()->SetMaterial(mat);
	ret->AddComponent<CubeOutlineRenderer>()->m_LineWidth = 2;
	ret->GetComponent<MeshRenderer>()->bRayCast = true;
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

void StageController::SaveData(const string& path)
{
	std::ofstream file(path, std::ios::out | std::ios::binary);
	//std::ofstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file for saving data!" << std::endl;
		return;
	}
	// 保存父物体
	file << this->gameobject->Name << " " << this->gameobject->GetTransform()->GetLocalPosition() << " " << this->gameobject->GetTransform()->GetLocalRotation() << " " << this->gameobject->GetTransform()->GetLocalScale() << std::endl;

	// 保存A舞台块数据
	for (const auto& stage : m_AStage)
	{
		file << stage->Name << " " << stage->GetTransform()->GetLocalPosition() << " "
			<< stage->GetTransform()->GetLocalRotation() << " " << stage->GetTransform()->GetLocalScale() << std::endl;
	}

	// 保存B1舞台块数据
	for (const auto& stage : m_B1Stage)
	{
		file << stage->Name << " " << stage->GetTransform()->GetLocalPosition() << " "
			<< stage->GetTransform()->GetLocalRotation() << " " << stage->GetTransform()->GetLocalScale() << std::endl;
	}

	// 保存B2舞台块数据
	for (const auto& stage : m_B2Stage)
	{
		file << stage->Name << " " << stage->GetTransform()->GetLocalPosition() << " "
			<< stage->GetTransform()->GetLocalRotation() << " " << stage->GetTransform()->GetLocalScale() << std::endl;
	}

	// 保存BT舞台块数据
	for (const auto& stage : m_BTStage)
	{
		file << stage->Name << " " << stage->GetTransform()->GetLocalPosition() << " "
			<< stage->GetTransform()->GetLocalRotation() << " " << stage->GetTransform()->GetLocalScale() << std::endl;
	}

	// 保存C舞台块数据
	for (const auto& stage : m_CStage)
	{
		file << stage->Name << " " << stage->GetTransform()->GetLocalPosition() << " "
			<< stage->GetTransform()->GetLocalRotation() << " " << stage->GetTransform()->GetLocalScale() << std::endl;
	}

	file.close();
}

void StageController::BStageMotion(float deltatime)
{
	// 模拟波浪运动
	m_BTime += deltatime;
	// 记录B1区的初始Y位置
	static float B1Y = m_B1Stage[0]->GetTransform()->GetWorldPosition().y;
	// B1
	for (auto stage : m_B1Stage)
	{
		auto pos = stage->GetTransform()->GetWorldPosition();
		stage->GetTransform()->SetWorldPosition(CVector(pos.x, ComputeWaveDisplacement(m_BTime, stage->GetTransform()->GetWorldPosition().x, 20, 3, 4, true) + B1Y, pos.z));
	}
	// B2
	static float B2Y = m_B2Stage[0]->GetTransform()->GetWorldPosition().y;
	for (auto stage : m_B2Stage)
	{
		auto pos = stage->GetTransform()->GetWorldPosition();
		stage->GetTransform()->SetWorldPosition(CVector(pos.x, ComputeWaveDisplacement(m_BTime, stage->GetTransform()->GetWorldPosition().x, 20, 3, 4, true) + B2Y, pos.z));
	}
}

void StageController::CStageMotion(float deltatime)
{
	// 自旋转 & 水平来回运动 [-5, 5]
	m_CTime += deltatime;
	// 记录C区的初始Y位置
	static float CX[8] = {
	m_CStage[0]->GetTransform()->GetWorldPosition().x,
	m_CStage[1]->GetTransform()->GetWorldPosition().x,
	m_CStage[2]->GetTransform()->GetWorldPosition().x,
	m_CStage[3]->GetTransform()->GetWorldPosition().x,
	m_CStage[4]->GetTransform()->GetWorldPosition().x,
	m_CStage[5]->GetTransform()->GetWorldPosition().x,
	m_CStage[6]->GetTransform()->GetWorldPosition().x,
	m_CStage[7]->GetTransform()->GetWorldPosition().x,
	};
	for (int i = 0; i < 8; ++i)
	{
		// 水平移动
		auto pos = m_CStage[i]->GetTransform()->GetWorldPosition();
		m_CStage[i]->GetTransform()->SetWorldPosition(CVector(ComputeWaveDisplacement(m_CTime, 0, 20 + i, 5, 2) + CX[i], pos.y, pos.z));

		// 自旋转
		m_CStage[i]->GetTransform()->Rotate(CVector::Up(), m_rotRate * deltatime);
	}
}

float StageController::ComputeWaveDisplacement(float t, float x, float T, float A, float speed, bool isABS)
{
	// 计算垂直位移，根据正弦函数生成波浪形状
	return isABS ? abs(A * sinf((2 * PI / T) * (x + speed * t))) : (A * sinf((2 * PI / T) * (x + speed * t)));
}

void StageController::LoadData(const string& path, bool ignoreA, bool ignoreB, bool ignoreC)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
	//std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file for loading data!" << std::endl;
		return;
	}

	std::string line;
	// 读入父物体
	{
		std::getline(file, line);
		std::stringstream ss(line);
		std::string name;
		CVector position, scale;
		CQuaternion rotation;
		ss >> name;
		ss >> position;
		ss >> rotation;
		ss >> scale;

		this->gameobject->GetTransform()->SetLocalPosition(position);
		this->gameobject->GetTransform()->SetLocalRotation(rotation);
		this->gameobject->GetTransform()->SetLocalScale(scale);
	}

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string name;
		CVector position, scale;
		CQuaternion rotation;
		ss >> name;
		ss >> position;
		ss >> rotation;
		ss >> scale;

		std::vector<GameObject*>& stages = m_AStage;
		if (name[0] == 'A')
		{
			if (ignoreA)
			{
				continue;;
			}
			stages = m_AStage;
		}
		else if (name[0] == 'B')
		{
			if (ignoreB)
			{
				continue;;
			}
			if (name[1] == '1')
			{
				stages = m_B1Stage;
			}
			else if (name[1] == '2')
			{
				stages = m_B2Stage;
			}
			else if (name[1] == 'T')
			{
				stages = m_BTStage;
			}
		}
		else if (name[0] == 'C')
		{
			if (ignoreC)
			{
				continue;;
			}
			stages = m_CStage;
		}
		for (auto stage : stages)
		{
			if (stage->Name == name)
			{
				stage->GetTransform()->SetLocalPosition(position);
				stage->GetTransform()->SetLocalRotation(rotation);
				stage->GetTransform()->SetLocalScale(scale);
				break;
			}
		}
	}

	file.close();
}