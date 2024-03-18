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
		// 销毁挂载的组件
		for (Component* component : m_components)
		{
			delete component;
		}
		m_components.clear();


		if (this->m_parent)
		{
			this->m_parent->RemoveChild(this);
		}

		// 销毁子物体
		for (GameObject* child : m_children)
		{
			delete child;
		}
		m_children.clear();

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




	template <typename T, typename/* = std::enable_if_t<std::is_base_of<Component, T>::value>*/ >
	T* GameObject::AddComponent()
	{
		T* newComponent = new T(*this);
		m_components.push_back(newComponent);
		return newComponent;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	GameObject::GetComponentsInParent()
	{
		// 从当前物体开始搜索
		std::vector<T*> result;
		GameObject* parent = this;
		while (parent != nullptr) {
			std::vector<T*> comps = parent->GetComponents<T>();
			result.insert(result.end(), comps.begin(), comps.end());
			parent = parent->m_parent;
		}
		return result;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* GameObject::GetComponentInParent()
	{
		GameObject* parent = this;
		while (parent != nullptr) {
			T* comp = parent->GetComponent<T>();
			if (comp != nullptr) {
				return comp;
			}
			parent = parent->m_parent;
		}
		return nullptr;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	GameObject::GetComponentsInChildren()
	{
		std::vector<T*> result;

		// 从当前物体开始搜索
		std::vector<T*> comps = GetComponents<T>();
		result.insert(result.end(), comps.begin(), comps.end());

		// 从子物体中搜索
		for (GameObject* child : this->m_components) {
			std::vector<T*> childComps = child->GetComponentsInChildren<T>();
			result.insert(result.end(), childComps.begin(), childComps.end());
		}

		return result;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* GameObject::GetComponentInChildren()
	{
		// 从当前物体开始搜索
		T* comp = GetComponent<T>();
		if (comp != nullptr) {
			return comp;
		}

		// 从子物体中搜索
		for (GameObject* child : this->m_components) {
			comp = child->GetComponentInChildren<T>();
			if (comp != nullptr) {
				return comp;
			}
		}

		return nullptr;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	GameObject::GetComponents()
	{
		std::vector<T*> result;
		for (Component* comp : this->m_components) {
			if (dynamic_cast<T*>(comp) != nullptr) {
				result.push_back(dynamic_cast<T*>(comp));
			}
		}
		return result;
	}

	Engine::Transform* GameObject::GetTransform()
	{
		return transform;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* GameObject::GetComponent()
	{
		for (Component* comp : this->m_components) {
			if (dynamic_cast<T*>(comp) != nullptr) {
				return dynamic_cast<T*>(comp);
			}
		}
		return nullptr;
	}


}