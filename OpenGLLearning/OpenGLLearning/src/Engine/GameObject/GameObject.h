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
		// �任��� -> �����Ƴ���ÿ��GameObject���У�����Component������������GameObject.transform������ComponentList�����ǿ���GetComponent -> ջ
		Transform* transform;
	public:
		Transform* GetTransform();

	protected:
		// ���ص���� -> ջ
		std::vector<Component*> m_components;

		// ������
		GameObject* m_parent;

		// ֱ��������
		std::vector<GameObject*> m_children;

		bool IsDelete = false;

	public:
		// ��ȡ���
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponent();

		// ��ȡ���
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponents();

		// ��ȡ�������е����, �ȴӵ�ǰ���忪ʼ��
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponentInChildren();

		// ��ȡ�������е����, �ȴӵ�ǰ���忪ʼ��
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInChildren();

		// ��ȡ�������е����, �ȴӵ�ǰ���忪ʼ��
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* GetComponentInParent();

		// ��ȡ�������е����, �ȴӵ�ǰ���忪ʼ��
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInParent();

		// �������
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		T* AddComponent();

		// ����ֱ��Object.Destory(GetComponent<T>())

		// ���ø�����
		// Ĭ�ϱ�������任
		void SetParent(GameObject& obj, bool stayWorldTransform = true);

		// ��ø�����
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
		// �ӵ�ǰ���忪ʼ����
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

		// �ӵ�ǰ���忪ʼ����
		std::vector<T*> comps = GetComponents<T>();
		result.insert(result.end(), comps.begin(), comps.end());

		// ��������������
		for (GameObject* child : this->m_components) {
			std::vector<T*> childComps = child->GetComponentsInChildren<T>();
			result.insert(result.end(), childComps.begin(), childComps.end());
		}

		return result;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* GameObject::GetComponentInChildren()
	{
		// �ӵ�ǰ���忪ʼ����
		T* comp = GetComponent<T>();
		if (comp != nullptr) {
			return comp;
		}

		// ��������������
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
