#include "Camera.h"
#include "../Global/GlobalManager.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "../Math/CMath.h"
#include "../Math/CEuler.h"
#include "glm/gtc/type_ptr.hpp"

namespace Engine
{

	void Camera::SetProjectionType(ProjectionType projectionType)
	{
		m_ProjectionType = projectionType;
	}

	void Camera::SetFOV(float fov)
	{
		m_FOV = fov;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
	}

	void Camera::SetOrthoSize(float size)
	{
		m_OrthoSize = size;
	}

	void Camera::SetClippingPlanes(float nearClip, float farClip)
	{
		m_NearClip = nearClip;
		m_FarClip = farClip;
	}

	void Camera::SetRenderOrder(int order)
	{
		if (m_RenderOrder != order)
		{
			m_RenderOrder = order;
			GlobalManager::GetInstance().cameraManager->IsSorted = false;
		}
	}

	int Camera::GetViewportWidth() const
	{
		return GlobalManager::GetInstance().cameraManager->ViewportWidth;
	}

	int Camera::GetViewportHeight() const
	{
		return GlobalManager::GetInstance().cameraManager->ViewportHeight;
	}

	int Camera::GetRenderOrder() const
	{
		return m_RenderOrder;
	}

	float Camera::GetOrthoSize() const
	{
		return m_OrthoSize;
	}

	const Engine::CMatrix& Camera::GetProjectionMatrix()
	{
		updateProjectionMatrix();
		return m_ProjectionMatrix;
	}

	Engine::CMatrix Camera::GetViewMatrix() const
	{
		// 获取摄像机的位置和朝向
		CVector position = transform->GetWorldPosition();
		CVector target = position + transform->GetForward();
		CVector up = transform->GetUp();

		// 计算视图矩阵
		return CMatrix::lookAt(position, target, up);
	}

	void Camera::updateProjectionMatrix()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_ProjectionMatrix = CMatrix::perspective(CMath::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		}
		else if (m_ProjectionType == ProjectionType::Orthographic)
		{
			float halfWidth = m_AspectRatio * m_OrthoSize;
			m_ProjectionMatrix = CMatrix::ortho(-halfWidth, halfWidth, -m_OrthoSize, m_OrthoSize, m_NearClip, m_FarClip);
		}
	}

	float Camera::GetFOV() const
	{
		return m_FOV;
	}

	float Camera::GetAspectRatio() const
	{
		return m_AspectRatio;
	}

	float Camera::GetNearClip() const
	{
		return m_NearClip;
	}

	float Camera::GetFarClip() const
	{
		return m_FarClip;
	}

	Camera::ProjectionType Camera::GetProjectionType()
	{
		return m_ProjectionType;
	}

}