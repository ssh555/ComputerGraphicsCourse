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

	protected:
		virtual ~GameObject();

		void RemoveChild(GameObject* obj);
	};

}
