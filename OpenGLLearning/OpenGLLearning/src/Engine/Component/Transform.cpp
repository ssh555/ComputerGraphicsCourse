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
			// 如果有父物体，则计算世界坐标
			CVector worldScale = gameobject->m_parent->transform->GetWorldScale();
			CQuaternion worldRotation = gameobject->m_parent->transform->GetWorldRotation();
			CVector parentWorldPosition = gameobject->m_parent->transform->GetWorldPosition();
			CVector t(worldScale.x * m_localposition.x, worldScale.y * m_localposition.y, worldScale.z * m_localposition.z);

			// 应用缩放、旋转、平移变换
			return parentWorldPosition + (worldRotation * t);
		}
		else
		{
			// 如果没有父物体，则局部坐标就是世界坐标
			return m_localposition;
		}
	}


	void Transform::SetWorldPosition(const CVector& position)
	{
		SetDirty(true);
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
		SetDirty(true);
		m_localrotation = rotation;
	}

	void Transform::SetWorldRotation(const CQuaternion& rotation)
	{
		SetDirty(true);
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
		// 创建旋转四元数
		CQuaternion rotation = CQuaternion::quatFromAxisAngle(axis, CMath::radians(angle));

		// 应用旋转
		m_localrotation = rotation * m_localrotation;
	}

	void Transform::RotateAround(const CVector& point, const CVector& axis, float angle)
	{
		SetDirty(true);

		angle = CMath::radians(angle);
		// 将局部坐标系中的位置转换为世界坐标系中的位置
		CVector worldPoint = point;

		if (gameobject->m_parent)
		{
			worldPoint = gameobject->m_parent->transform->GetWorldTransform().posMul(worldPoint);
		}

		// 将世界坐标系中的位置转换为局部坐标系中的位置
		CVector localPoint = worldPoint;

		if (gameobject->m_parent)
		{
			localPoint = gameobject->m_parent->transform->GetWorldTransform().GetInverse().posMul(worldPoint);
		}

		// 将局部坐标系中的位置作为旋转中心
		CMatrix rotationCenter = CMatrix::translate(CMatrix(1.0f), localPoint);

		// 绕指定轴进行旋转
		CMatrix rotation = CMatrix::rotate(axis, angle);

		// 将旋转中心与旋转组合起来
		CMatrix transformMatrix = rotationCenter * rotation;

		// 更新局部变换
		CMatrix currentTransform = GetWorldTransform();
		CMatrix newTransform = transformMatrix * currentTransform;

		// 从新的变换矩阵中提取位置、旋转和缩放信息
		CVector newPosition = CMatrix::getTranslation(newTransform);
		CQuaternion newRotation = CQuaternion::quatFromMatrix(newTransform);
		CVector newScale = CMatrix::getScale(newTransform);

		// 设置新的位置、旋转和缩放
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