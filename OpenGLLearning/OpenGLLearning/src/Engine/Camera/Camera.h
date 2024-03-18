#pragma once
#include "../Component/Component.h"
#include "../Math/CMatrix.h"

namespace Engine
{
	class CVector;

	class Camera final : public Component
	{
		friend class CameraManager;
		friend class GameObject;

	private:
		Camera(GameObject* obj) : Component(obj, false) { }

	public:
		// 投影方式
		enum class ProjectionType { Perspective, Orthographic };

		// FOV(垂直轴), 纵横比, 近裁切面, 远裁切面, 投影方式
		//Camera(float fov, float aspectRatio, float nearClip, float farClip, ProjectionType projectionType)
		//    : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), m_ProjectionType(projectionType)
		//{
		//    updateProjectionMatrix();
		//}

		void SetProjectionType(ProjectionType projectionType);

		void SetFOV(float fov);

		void SetAspectRatio(float aspectRatio);

		void SetOrthoSize(float size);

		void SetClippingPlanes(float nearClip, float farClip);

		// void SetViewport(int x, int y, int offx, int offy)
		// {
		//    m_ViewportX = x;
		//    m_ViewportY = y;
		//    m_ViewportOffX = offx;
		//    m_ViewportOffY = offy;
		// }

		void SetRenderOrder(int order);

		// int GetViewportX() const { return m_ViewportX; }
		// int GetViewportY() const { return m_ViewportY; }
		int GetViewportWidth() const;
		int GetViewportHeight() const;
		int GetRenderOrder() const;
		float GetOrthoSize() const;

		const CMatrix& GetProjectionMatrix() const;

		// 获取摄像机的视图矩阵
		CMatrix GetViewMatrix() const;

	private:
		float m_FOV = 60.0f;
		float m_AspectRatio = 16.0f / 9.0f;
		float m_NearClip = 0.1f;
		float m_FarClip = 1000.0f;
		ProjectionType m_ProjectionType = ProjectionType::Perspective;
		CMatrix m_ProjectionMatrix;
		// int m_ViewportX = 0;
		// int m_ViewportY = 0;
		// int m_ViewportOffX = 1;
		// int m_ViewportOffY = 1;
		float m_OrthoSize = 3; // Orthographic size
		int m_RenderOrder = 0; // Default render order

		void updateProjectionMatrix();
	};
}

