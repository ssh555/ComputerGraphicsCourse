#pragma once
#include <vector>
#include "../GameObject/GameObject.h"

namespace Engine
{
	class GameObject;
	class Transform;
	class GlobalManager;

	class Component
	{
		friend class ComponentManager;
		friend class GameObject;

	public:
		void SetEnable(bool enable);

		bool GetEnable();


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
		T& GetComponentInParent();

		// 获取父物体中的组件, 先从当前物体开始找
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInParent();

	protected:
		// 挂载的GameObject
		Component(const GameObject* obj, bool enable = true);

		virtual ~Component();

	protected:
		virtual void Tick(float deltatime);

		virtual void LateTick(float deltatime);

		virtual void OnEnable();

		virtual void OnDisable();


	public:
		// 所在物体
		const GameObject* gameobject;
		// 所在物体的Transform
		const Transform* transform;

	private:
		bool m_enabled = false;

	};

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	Component::GetComponentsInParent()
	{
		return this->gameobject->GetComponentsInParent<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T& Component::GetComponentInParent()
	{
		return *this->gameobject->GetComponentInParent<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	Component::GetComponentsInChildren()
	{
		return this->gameobject->GetComponentsInChildren<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* Component::GetComponentInChildren()
	{
		return this->gameobject->GetComponentInChildren<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	Component::GetComponents()
	{
		return this->gameobject->GetComponents<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T* Component::GetComponent()
	{
		return this->gameobject->GetComponent<T>();
	}

}
