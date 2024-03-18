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

	protected:
		virtual ~GameObject();

		void RemoveChild(GameObject* obj);
	};

}
