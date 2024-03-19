#include "GameObject.h"
#include <xmemory>
#include "../Math/CVector.h"
#include "../Component/Transform.h"
#include <xtr1common>
#include <type_traits>

namespace Engine
{
	GameObject::GameObject() : transform(new Transform(this)), m_parent(nullptr) { }

	GameObject::~GameObject()
	{
		this->IsDelete = true;
		if (this->m_parent)
		{
			this->m_parent->RemoveChild(this);
		}

		// ����������
		for (GameObject* child : m_children)
		{
			if (child && !child->IsDelete)
			{
				delete child;
			}
		}
		m_children.clear();

		// ���ٹ��ص����
		for (Component* component : m_components)
		{
			delete component;
		}
		m_components.clear();

		delete transform;
	}

	void GameObject::RemoveChild(GameObject* obj)
	{
		auto it = std::find(this->m_children.begin(), this->m_children.end(), obj);
		if (it != this->m_children.end()) {
			this->m_children.erase(it);
		}
		obj->m_parent = nullptr;
	}

	void GameObject::SetParent(GameObject& obj, bool stayWorldTransform /*= true*/)
	{
		// ���Ҫ���õĸ������뵱ǰ��������ͬ����������в���
		if (m_parent == &obj)
			return;

		// ��¼��ǰ����������
		CVector worldPosition;
		if (stayWorldTransform)
		{
			worldPosition = transform->GetWorldPosition();
		}

		// �Ӹ������Ƴ�
		if (m_parent)
		{
			this->m_parent->RemoveChild(this);
		}

		this->m_parent = &obj;
		this->m_parent->m_children.push_back(this);
		// ����stayWorldTransform������������任
		if (stayWorldTransform)
		{
			// ��������������Ϊ֮ǰ��¼����������
			transform->SetWorldPosition(worldPosition);
		}
	}

	const GameObject* GameObject::GetParent() const
	{
		return m_parent;
	}

	const std::vector<GameObject*>& GameObject::GetChildren()
	{
		return m_children;
	}

	Engine::Transform* GameObject::GetTransform()
	{
		return transform;
	}



}