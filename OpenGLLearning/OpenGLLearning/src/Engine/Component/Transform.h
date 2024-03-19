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

		// ��ȡ�ֲ�����ϵ�е�ǰ����
		CVector GetForward() const;

		// ��ȡ�ֲ�����ϵ�е��Ϸ���
		CVector GetUp() const;

		// ��ȡ�ֲ�����ϵ�е�����
		CVector GetLeft() const;

		void Rotate(const CVector& axis, float angle);
		void RotateAround(const CVector& point, const CVector& axis, float angle);
	private:
		// λ��
		CVector m_localposition;

		// ��ת
		CQuaternion m_localrotation;

		// ����
		CVector m_localscale;

		CMatrix m_worldTransform;

		void SetDirty(bool dirty);
		bool IsDirty = true;

	};


}
