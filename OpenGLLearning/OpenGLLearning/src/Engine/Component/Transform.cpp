#include "transform.h"
#include "../GameObject/GameObject.h"


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
		m_localposition = position;
	}

	Engine::CVector Transform::GetWorldPosition() const
	{
		if (this->gameobject->m_parent)
		{
			// 如果有父物体，则计算世界坐标
			return gameobject->m_parent->transform->GetWorldPosition() * (gameobject->m_parent->transform->GetWorldRotation() * (gameobject->m_parent->transform->GetLocalScale() * m_localposition));
		}
		else
		{
			// 如果没有父物体，则局部坐标就是世界坐标
			return m_localposition;
		}
	}

	void Transform::SetWorldPosition(const CVector& position)
	{
		if (gameobject->m_parent)
		{
			// 如果有父物体，则计算局部坐标并设置
			m_localposition = gameobject->m_parent->transform->GetWorldRotation().GetInverse() * (position - gameobject->m_parent->transform->GetWorldPosition()) / gameobject->m_parent->transform->GetWorldScale();
		}
		else
		{
			// 如果没有父物体，则直接设置局部坐标
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
			// 如果有父物体，则计算世界旋转
			return gameobject->m_parent->transform->GetWorldRotation() * m_localrotation;
		}
		else
		{
			// 如果没有父物体，则局部旋转就是世界旋转
			return m_localrotation;
		}
	}

	void Transform::SetLocalRotation(const CQuaternion& rotation)
	{
		m_localrotation = rotation;
	}

	void Transform::SetWorldRotation(const CQuaternion& rotation)
	{
		if (gameobject->m_parent)
		{
			// 如果有父物体，则计算局部旋转并设置
			m_localrotation = (gameobject->m_parent->transform->GetWorldRotation()).GetInverse() * rotation;
		}
		else
		{
			// 如果没有父物体，则直接设置局部旋转
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
			// 如果有父物体，则计算世界缩放
			return CVector(
				gameobject->m_parent->transform->GetWorldScale().x * m_localscale.x,
				gameobject->m_parent->transform->GetWorldScale().y * m_localscale.y,
				gameobject->m_parent->transform->GetWorldScale().z * m_localscale.z
			);
		}
		else
		{
			// 如果没有父物体，则局部缩放就是世界缩放
			return m_localscale;
		}
	}

	void Transform::SetLocalScale(const CVector& scale)
	{
		m_localscale = scale;
	}

	Engine::CMatrix Transform::GetWorldTransform() const
	{
		CMatrix worldTransform(1);
		worldTransform = CMatrix::scale(worldTransform, GetWorldScale());
		worldTransform *= GetWorldRotation().ToCMatrix();
		worldTransform = CMatrix::translate(worldTransform, GetWorldPosition());
		return worldTransform;
	}

	void Transform::LookAt(const CVector& target)
	{
		CVector direction = (target - GetWorldPosition()).Normalized();
		CQuaternion rotation = CQuaternion::quatLookAt(direction, CVector::Up());
		SetWorldRotation(rotation);
	}

	void Transform::Translate(const CVector& translation)
	{
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

}