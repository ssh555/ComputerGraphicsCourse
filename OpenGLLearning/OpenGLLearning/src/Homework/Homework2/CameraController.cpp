#include "CameraController.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Math/CVector.h"
#include "Engine/Camera/CameraManager.h"
#include "Engine/Component/Transform.h"
#include "Engine/Math/CMatrix.h"
#include "Engine/Render/LineRenderer.h"
#include "Engine/Render/Material.h"
#include "Engine/Render/Mesh.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Math/CQuaternion.h"
#include <iostream>
#include <sstream>
#include <iomanip> // 用于设置浮点数精度
#include "Engine/Math/CEuler.h"
#include "CameraControllerUI.h"

using namespace Engine;

CameraController::CameraController(Engine::GameObject* obj) : Component(obj),
m_camera(this->gameobject->GetComponent<Camera>())
{
	GlobalManager::GetInstance().testMenu->RegisterTest<CameraControllerUI>("CameraController");


	// 点选
	m_lineRenderer = (new GameObject())->AddComponent<LineRenderer>();
	m_lineRenderer->m_LineWidth = 5.0f;
	m_lineRenderer->Color = CVector(1.0f, 0.0f, 0.0f);
	float lineVertices[] = {
		0,0,0,
		0,0,1
	};
	unsigned int lineIndices[] = { 0, 1 };
	Mesh* lineMesh = new Mesh(lineVertices, 6, lineIndices, 2);
	m_lineRenderer->SetMesh(lineMesh);
	m_lineRenderer->SetEnable(true);



	GlobalManager::GetInstance().inputManager->RegisterMouseButtonCallback(InputManager::MouseButton::Left, [this](InputManager::MouseButton mtype, InputManager::MouseButtonAction action, double xpos, double ypos)
		{
			if (action == InputManager::MouseButtonAction::Press)
			{
				// 获取窗口尺寸
				int screenWidth, screenHeight;
				GlobalManager::GetInstance().GetViewPortSize(screenWidth, screenHeight);

				// 标准化鼠标位置
				float normalizedX = (2.0f * xpos) / screenWidth - 1.0f;
				float normalizedY = 1.0f - (2.0f * ypos) / screenHeight;

				// 生成射线起点
				CVector cameraPosition = m_camera->transform->GetWorldPosition();

				// 生成射线方向
				CVector rayClipCoords(normalizedX, normalizedY, -1.0f); // 射线在裁剪空间的坐标
				CMatrix inversePV = (m_camera->GetProjectionMatrix() * m_camera->GetViewMatrix()).GetInverse();
				CVector rayEyeCoords = inversePV.posMul(rayClipCoords); // 射线在视图空间的坐标
				CVector rayDirection = (m_camera->transform->GetWorldTransform().GetInverse().vecMul(rayEyeCoords)).Normalized(); // 射线在世界空间的方向

				// 进行射线检测
				float hitDistance = 500.0f;
				MeshRenderer* hitObject = MeshRenderer::RayCast(cameraPosition, rayDirection, hitDistance);

				if (hitObject)
				{
					std::cout << hitObject->gameobject->Name << std::endl;
					// 如果命中了物体，可以在这里执行相关操作
					// hitDistance 可以用于进一步处理，比如确定点击位置在物体表面的哪个点上
				}

				m_lineRenderer->transform->SetWorldPosition(cameraPosition);
				m_lineRenderer->transform->LookAt(cameraPosition + rayDirection * hitDistance);
				m_lineRenderer->transform->SetLocalScale(CVector(1, 1, 1 * hitDistance));

			}
		});
}

void CameraController::Tick(float deltatime)
{
}

void CameraController::LateTick(float deltatime)
{
	// 移动摄像机
	Move();

	// 旋转摄像机
	Rotate();
}

void CameraController::Move()
{
	if(GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::A))
	{
		this->transform->Translate(CVector::Left() * this->moveSpeed);
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::D))
	{
		this->transform->Translate(CVector::Right() * this->moveSpeed);
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::W))
	{
		this->transform->Translate(CVector::Forward() * this->moveSpeed);
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::S))
	{
		this->transform->Translate(CVector::Backward() * this->moveSpeed);
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Q))
	{
		this->transform->Translate(CVector::Up() * this->moveSpeed);
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::E))
	{
		this->transform->Translate(CVector::Down() * this->moveSpeed);
		PrintCurrentState();
	}

	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::Equal))
	{
		this->moveSpeed += 0.01;
		PrintCurrentState();
	}
	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::Minus))
	{
		this->moveSpeed -= 0.01;
		PrintCurrentState();
	}
}

void CameraController::Rotate()
{

}

void CameraController::PrintCurrentState()
{
	auto pos = this->transform->GetWorldPosition();
	std::stringstream posStream;
	posStream << std::fixed << std::setprecision(2) << "[position = (x = " << pos.x << ", y = " << pos.y << ", z = " << pos.z << "); MoveSpeed = " << moveSpeed << "]";
	std::string posStr = posStream.str();
	auto rot = this->transform->GetWorldRotation().ToCEuler();
	std::stringstream rotStream;
	rotStream << std::fixed << std::setprecision(2) << "[rotation = (x = " << rot.h << ", y = " << rot.p << ", z = " << rot.b << "); RotSpeed = " << moveSpeed << "]";
	std::string rotStr = rotStream.str();

	std::cout << "当前摄像机数据为: " + posStr + "\t" + rotStr << std::endl;
}

