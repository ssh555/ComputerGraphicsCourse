#include "CameraController.h"
#include "Engine/Global/GlobalManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Render/MeshRenderer.h"
#include "Engine/Camera/Camera.h"
#include "Engine/Math/CVector.h"
#include "Engine/Camera/CameraManager.h"
#include "Engine/Component/Transform.h"
#include "Engine/Math/CMatrix.h"
#include "Engine/Render/Material.h"
#include "Engine/Render/Mesh.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Math/CQuaternion.h"
#include <iostream>
#include <sstream>
#include <iomanip> // 用于设置浮点数精度
#include "Engine/Math/CEuler.h"
#include "CameraControllerUI.h"
#include "Engine/Render/LineRenderer.h"

using namespace Engine;

CameraController::CameraController(Engine::GameObject* obj) : Component(obj),
m_camera(this->gameobject->GetComponent<Camera>()),
m_lineRenderer(nullptr),
hitPoint(CVector::Zero()),
SelectedPoint(CVector::Zero()),
hitT(0)
{
	GlobalManager::GetInstance().testMenu->RegisterTest<CameraControllerUI>("CameraController");

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
}

void CameraController::Tick(float deltatime)
{
	auto mgr = GlobalManager::GetInstance().inputManager;
	// 左键射线检测
	if (mgr->GetKeyDown(InputManager::Key::MouseLeft))
	{
		// 生成射线起点
		CVector cameraPosition = m_camera->transform->GetWorldPosition();
		double xpos, ypos;
		mgr->GetMousePos(xpos, ypos);
		// 生成射线方向
		CVector rayClipCoords((float)xpos, (float)ypos, 1.0f); // 射线在裁剪空间的坐标
		CVector rayDirection = m_camera->ScreenToWorldOnPoint(rayClipCoords);

		rayDirection = rayDirection - cameraPosition;

		// 进行射线检测
		float hitDistance = 500.0f;
		MeshRenderer* hitObject = MeshRenderer::RayCast(cameraPosition, rayDirection, hitDistance, hitPoint);
		hitT = (hitPoint - cameraPosition).len();

		if (hitObject)
		{
			SelectGameObject(hitObject->gameobject);
		}
		else
		{
			SelectGameObject(nullptr);
		}
		//m_lineRenderer->transform->SetWorldPosition(cameraPosition);
		//m_lineRenderer->transform->LookAt(cameraPosition + rayDirection * hitDistance);
		//m_lineRenderer->transform->SetLocalScale(CVector(1, 1, 1 * hitDistance));
	}
	// 左键按住移动
	if (mgr->GetKey(InputManager::Key::MouseLeft) && CurSelected)
	{
		// 垂直移动
		if (CurSelected->Name[0] == 'B')
		{
			double xpos, ypos;
			mgr->GetMousePos(xpos, ypos);
			// 生成射线方向
			CVector rayClipCoords((float)xpos, (float)ypos, 1.0f); // 射线在裁剪空间的坐标
			CVector rayDirection = m_camera->ScreenToWorldOnPoint(rayClipCoords);
			CVector cameraPosition = m_camera->transform->GetWorldPosition();
			rayDirection = (rayDirection - cameraPosition).Normalized();
			// 这一次命中点
			float yoff = ((cameraPosition + rayDirection * hitT) - hitPoint).y;
			CurSelected->GetTransform()->SetWorldPosition(SelectedPoint + CVector(0, yoff, 0));
		}
		// 水平移动
		else if (CurSelected->Name[0] == 'C')
		{
			double xpos, ypos;
			mgr->GetMousePos(xpos, ypos);
			// 生成射线方向
			CVector rayClipCoords((float)xpos, (float)ypos, 1.0f); // 射线在裁剪空间的坐标
			CVector rayDirection = m_camera->ScreenToWorldOnPoint(rayClipCoords);
			CVector cameraPosition = m_camera->transform->GetWorldPosition();
			rayDirection = (rayDirection - cameraPosition).Normalized();
			// 这一次命中点
			float xoff = ((cameraPosition + rayDirection * hitT) - hitPoint).x;
			CurSelected->GetTransform()->SetWorldPosition(SelectedPoint + CVector(xoff, 0, 0));
		}
	}
	// 右键按住旋转
	if (mgr->GetKey(InputManager::Key::MouseRight) && CurSelected)
	{
		if (CurSelected->Name[0] == 'C')
		{
			float xoff, yoff;
			mgr->GetMouseOffset(xoff, yoff);
			// 只会旋转Y -> 水平旋转
			CurSelected->GetTransform()->Rotate(CVector::Up(), xoff * deltatime * selectRotSpeed);
		}
	}
}

void CameraController::LateTick(float deltatime)
{
	// 移动摄像机
	Move(deltatime);

	// 旋转摄像机
	Rotate(deltatime);
}

void CameraController::Move(float deltatime)
{
	if(GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::A))
	{
		this->transform->Translate(this->transform->GetLeft() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::D))
	{
		this->transform->Translate(-this->transform->GetLeft() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::W))
	{
		this->transform->Translate(this->transform->GetForward() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::S))
	{
		this->transform->Translate(-this->transform->GetForward() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::Q))
	{
		this->transform->Translate(this->transform->GetUp() * this->moveSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::E))
	{
		this->transform->Translate(-this->transform->GetUp() * this->moveSpeed * deltatime);
	}

	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::Equal) || GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::NumPadAdd))
	{
		this->moveSpeed += 1;
	}
	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::Minus) || GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::NumPadSubtract))
	{
		this->moveSpeed -= 1;
	}
}

void CameraController::Rotate(float deltatime)
{
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::J))
	{
		if (CurSelected)
		{
			auto t = CurSelected->GetTransform();
			this->transform->RotateAround(t->GetWorldPosition(), CVector::Up(), -this->rotSpeed * deltatime);
		}
		else
		{
			this->transform->Rotate(this->transform->GetUp(), this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::L))
	{
		if (CurSelected)
		{
			auto t = CurSelected->GetTransform();
			this->transform->RotateAround(t->GetWorldPosition(), CVector::Up(), this->rotSpeed * deltatime);
		}
		else
		{
			// 子空间
			this->transform->Rotate(this->transform->GetUp(), -this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::K))
	{
		if (CurSelected)
		{
			auto t = CurSelected->GetTransform();
			this->transform->RotateAround(t->GetWorldPosition(), -this->transform->GetLeft(), this->rotSpeed * deltatime);
		}
		else
		{
			this->transform->Rotate(this->transform->GetLeft(), this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::I))
	{
		if (CurSelected)
		{
			auto t = CurSelected->GetTransform();
			this->transform->RotateAround(t->GetWorldPosition(), this->transform->GetLeft(), this->rotSpeed * deltatime);
		}
		else
		{
			this->transform->Rotate(this->transform->GetLeft(), -this->rotSpeed * deltatime);
		}
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::U))
	{
		this->transform->Rotate(this->transform->GetForward(), -this->rotSpeed * deltatime);
	}
	if (GlobalManager::GetInstance().inputManager->GetKey(InputManager::Key::O))
	{
		this->transform->Rotate(this->transform->GetForward(), this->rotSpeed * deltatime);
	}

	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::RightBracket))
	{
		this->rotSpeed += 1;
	}
	if (GlobalManager::GetInstance().inputManager->GetKeyDown(InputManager::Key::LeftBracket))
	{
		this->rotSpeed -= 1;
	}
}

void CameraController::SelectGameObject(GameObject* obj)
{
	if (CurSelected == obj)
	{
		if(CurSelected)
			SelectedPoint = CurSelected->GetTransform()->GetWorldPosition();
		return;
	}
	if (CurSelected)
	{

		auto comp = CurSelected->GetComponent<LineRenderer>();
		if (comp)
		{
			comp->SetEnable(false);
		}
	}
	CurSelected = obj;
	if (CurSelected)
	{
		//// BT不可选中
		//if (CurSelected->Name[1] == 'T')
		//{
		//	CurSelected = nullptr;
		//	return;
		//}
		SelectedPoint = CurSelected->GetTransform()->GetWorldPosition();
		auto comp = CurSelected->GetComponent<LineRenderer>();
		if (comp)
		{
			comp->SetEnable(true);
		}
	}
}

