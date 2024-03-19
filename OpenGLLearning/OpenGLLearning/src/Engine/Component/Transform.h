#pragma once
#include "Component.h"
#include "../Math/CVector.h"
#include "../Math/CMatrix.h"
#include "../Math/CQuaternion.h"

namespace Engine
{
	class GameObject;
	class Component;
	class CVector;
	class CMatrix;
	class CQuaternion;

	class Transform final : public Component
	{
		friend class GameObject;

	private:
		Transform(GameObject* obj);

	public:
		CVector GetLocalPosition() const;

		void SetLocalPosition(const CVector& position);

		CVector GetWorldPosition() const;

		void SetWorldPosition(const CVector& position);

		CQuaternion GetLocalRotation() const;

		CQuaternion GetWorldRotation() const;

		void SetLocalRotation(const CQuaternion& rotation);

		void SetWorldRotation(const CQuaternion& rotation);

		CVector GetLocalScale() const;

		CVector GetWorldScale() const;

		void SetLocalScale(const CVector& scale);

		CMatrix GetWorldTransform();

		void LookAt(const CVector& target);

		void Translate(const CVector& translation);

		// 获取局部坐标系中的前方向
		CVector GetForward() const;

		// 获取局部坐标系中的上方向
		CVector GetUp() const;

		// 获取局部坐标系中的左方向
		CVector GetLeft() const;

		void Rotate(const CVector& axis, float angle);
		void RotateAround(const CVector& point, const CVector& axis, float angle);
	private:
		// 位置
		CVector m_localposition;

		// 旋转
		CQuaternion m_localrotation;

		// 缩放
		CVector m_localscale;

		CMatrix m_worldTransform;

		void SetDirty(bool dirty);
		bool IsDirty = true;

	};


}
