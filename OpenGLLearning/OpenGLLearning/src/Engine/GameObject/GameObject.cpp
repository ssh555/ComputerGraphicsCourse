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

		// 销毁子物体
		for (GameObject* child : m_children)
		{
			if (child && !child->IsDelete)
			{
				delete child;
			}
		}
		m_children.clear();

		// 销毁挂载的组件
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
		// 如果要设置的父物体与当前父物体相同，则无需进行操作
		if (m_parent == &obj)
			return;

		// 记录当前的世界坐标
		CVector worldPosition;
		if (stayWorldTransform)
		{
			worldPosition = transform->GetWorldPosition();
		}

		// 从父物体移除
		if (m_parent)
		{
			this->m_parent->RemoveChild(this);
		}

		this->m_parent = &obj;
		this->m_parent->m_children.push_back(this);
		// 根据stayWorldTransform参数更新世界变换
		if (stayWorldTransform)
		{
			// 将世界坐标设置为之前记录的世界坐标
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