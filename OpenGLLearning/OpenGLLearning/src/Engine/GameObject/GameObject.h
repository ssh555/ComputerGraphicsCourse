#pragma once
#include <vector>

namespace Engine
{
	class Component;
	class Transform;

	class GameObject
	{
		friend class Transform;
		friend class Component;
	protected:
		// 变换组件 -> 不可移除，每个GameObject都有，所有Component都会引用所在GameObject.transform，不进ComponentList，但是可以GetComponent -> 栈
		Transform* transform;
	public:
		Transform* GetTransform();

	protected:
		// 挂载的组件 -> 栈
		std::vector<Component*> m_components;

		// 父物体
		GameObject* m_parent;

		// 直接子物体
		std::vector<GameObject*> m_children;

		bool IsDelete = false;

	public:
		// 获取组件
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponent();

		// 获取组件
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponents();

		// 获取子物体中的组件, 先从当前物体开始找
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponentInChildren();

		// 获取子物体中的组件, 先从当前物体开始找
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInChildren();

		// 获取父物体中的组件, 先从当前物体开始找
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponentInParent();

		// 获取父物体中的组件, 先从当前物体开始找
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInParent();

		// 加入组件
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* AddComponent();

		// 销毁直接Object.Destory(GetComponent<T>())

		// 设置父物体
		// 默认保留世界变换
		void SetParent(GameObject& obj, bool stayWorldTransform = true);

		// 获得父物体
		const GameObject* GetParent() const;

		const std::vector<GameObject*>& GetChildren();

	public:
		GameObject();
		virtual ~GameObject();

	protected:

		void RemoveChild(GameObject* obj);
	};

	template <typename T, typename/* = std::enable_if_t<std::is_base_of<Component, T>::value>*/ >
	T* GameObject::AddComponent()
	{
		T* newComponent = new T(this);
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
