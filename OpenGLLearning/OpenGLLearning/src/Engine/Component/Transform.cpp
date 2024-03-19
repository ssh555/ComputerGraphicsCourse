#include "transform.h"
#include "../GameObject/GameObject.h"
#include "../Math/CMath.h"
#include "../Math/CEuler.h"


namespace Engine
{
	Transform::Transform(GameObject* obj) : Component(obj, false),
		m_localposition(CVector::Zero()), m_localrotation(CQuaternion::Identity()), m_localscale(CVector::One())
	{
	}

	Engine::CVector Transform::GetLocalPosition() const
	{
		return m_localposition;
	}

	void Transform::SetLocalPosition(const CVector& position)
	{
		SetDirty(true);
		m_localposition = position;
	}

	Engine::CVector Transform::GetWorldPosition() const
	{
		if (this->gameobject->m_parent)
		{
			// ����и����壬�������������
			CVector worldScale = gameobject->m_parent->transform->GetWorldScale();
			CQuaternion worldRotation = gameobject->m_parent->transform->GetWorldRotation();
			CVector parentWorldPosition = gameobject->m_parent->transform->GetWorldPosition();
			CVector t(worldScale.x * m_localposition.x, worldScale.y * m_localposition.y, worldScale.z * m_localposition.z);

			// Ӧ�����š���ת��ƽ�Ʊ任
			return parentWorldPosition + (worldRotation * t);
		}
		else
		{
			// ���û�и����壬��ֲ����������������
			return m_localposition;
		}
	}


	void Transform::SetWorldPosition(const CVector& position)
	{
		SetDirty(true);
		if (gameobject->m_parent)
		{
			// ����и����壬�����ֲ����겢����
			m_localposition = gameobject->m_parent->transform->GetWorldRotation().GetInverse() * (position - gameobject->m_parent->transform->GetWorldPosition()) / gameobject->m_parent->transform->GetWorldScale();
		}
		else
		{
			// ���û�и����壬��ֱ�����þֲ�����
			m_localposition = position;
		}
	}

	Engine::CQuaternion Transform::GetLocalRotation() const
	{
		return m_localrotation;
	}

	Engine::CQuaternion Transform::GetWorldRotation() const
	{
		if (gameobject->m_parent)
		{
			// ����и����壬�����������ת
			return gameobject->m_parent->transform->GetWorldRotation() * m_localrotation;
		}
		else
		{
			// ���û�и����壬��ֲ���ת����������ת
			return m_localrotation;
		}
	}

	void Transform::SetLocalRotation(const CQuaternion& rotation)
	{
		SetDirty(true);
		m_localrotation = rotation;
	}

	void Transform::SetWorldRotation(const CQuaternion& rotation)
	{
		SetDirty(true);
		if (gameobject->m_parent)
		{
			// ����и����壬�����ֲ���ת������
			m_localrotation = (gameobject->m_parent->transform->GetWorldRotation()).GetInverse() * rotation;
		}
		else
		{
			// ���û�и����壬��ֱ�����þֲ���ת
			m_localrotation = rotation;
		}
	}

	Engine::CVector Transform::GetLocalScale() const
	{
		return m_localscale;
	}

	Engine::CVector Transform::GetWorldScale() const
	{
		if (gameobject->m_parent)
		{
			// ����и����壬�������������
			return CVector(
				gameobject->m_parent->transform->GetWorldScale().x * m_localscale.x,
				gameobject->m_parent->transform->GetWorldScale().y * m_localscale.y,
				gameobject->m_parent->transform->GetWorldScale().z * m_localscale.z
			);
		}
		else
		{
			// ���û�и����壬��ֲ����ž�����������
			return m_localscale;
		}
	}

	void Transform::SetLocalScale(const CVector& scale)
	{
		SetDirty(true);
		m_localscale = scale;
	}

	Engine::CMatrix Transform::GetWorldTransform()
	{
		if (IsDirty)
		{
			IsDirty = false;
			CMatrix worldTransform(1);
			worldTransform = CMatrix::scale(worldTransform, GetWorldScale());
			worldTransform *= GetWorldRotation().ToCMatrix();
			worldTransform = CMatrix::translate(worldTransform, GetWorldPosition());
			m_worldTransform = worldTransform;
		}


		return m_worldTransform;
	}

	void Transform::LookAt(const CVector& target)
	{
		SetDirty(true);
		CVector direction = (target - GetWorldPosition()).Normalized();
		CQuaternion rotation = CQuaternion::quatLookAt(direction, CVector::Up());
		SetWorldRotation(rotation);
	}

	void Transform::Translate(const CVector& translation)
	{
		SetDirty(true);
		m_localposition += m_localrotation * translation;
	}

	Engine::CVector Transform::GetForward() const
	{
		return m_localrotation * CVector::Forward();
	}

	Engine::CVector Transform::GetUp() const
	{
		return m_localrotation * CVector::Up();
	}

	Engine::CVector Transform::GetLeft() const
	{
		return m_localrotation * CVector::Left();
	}

	void Transform::Rotate(const CVector& axis, float angle)
	{
		SetDirty(true);
		// ������ת��Ԫ��
		CQuaternion rotation = CQuaternion::quatFromAxisAngle(axis, CMath::radians(angle));

		// Ӧ����ת
		m_localrotation = rotation * m_localrotation;
	}

	void Transform::RotateAround(const CVector& point, const CVector& axis, float angle)
	{
		SetDirty(true);

		angle = CMath::radians(angle);
		// ���ֲ�����ϵ�е�λ��ת��Ϊ��������ϵ�е�λ��
		CVector worldPoint = point;

		if (gameobject->m_parent)
		{
			worldPoint = gameobject->m_parent->transform->GetWorldTransform().posMul(worldPoint);
		}

		// ����������ϵ�е�λ��ת��Ϊ�ֲ�����ϵ�е�λ��
		CVector localPoint = worldPoint;

		if (gameobject->m_parent)
		{
			localPoint = gameobject->m_parent->transform->GetWorldTransform().GetInverse().posMul(worldPoint);
		}

		// ���ֲ�����ϵ�е�λ����Ϊ��ת����
		CMatrix rotationCenter = CMatrix::translate(CMatrix(1.0f), localPoint);

		// ��ָ���������ת
		CMatrix rotation = CMatrix::rotate(axis, angle);

		// ����ת��������ת�������
		CMatrix transformMatrix = rotationCenter * rotation;

		// ���¾ֲ��任
		CMatrix currentTransform = GetWorldTransform();
		CMatrix newTransform = transformMatrix * currentTransform;

		// ���µı任��������ȡλ�á���ת��������Ϣ
		CVector newPosition = CMatrix::getTranslation(newTransform);
		CQuaternion newRotation = CQuaternion::quatFromMatrix(newTransform);
		CVector newScale = CMatrix::getScale(newTransform);

		// �����µ�λ�á���ת������
		SetLocalPosition(newPosition);
		SetLocalRotation(newRotation);
		SetLocalScale(newScale);
	}

	void Transform::SetDirty(bool dirty)
	{
		this->IsDirty = dirty;
		if(this->IsDirty)
			for (auto obj : this->gameobject->GetChildren())
			{
				obj->GetTransform()->SetDirty(IsDirty);
			}
	}

}