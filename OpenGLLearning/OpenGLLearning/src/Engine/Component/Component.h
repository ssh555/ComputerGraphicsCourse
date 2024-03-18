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
		T& GetComponentInParent();

		// ��ȡ�������е����, �ȴӵ�ǰ���忪ʼ��
		template <typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::vector<T*> GetComponentsInParent();

	protected:
		// ���ص�GameObject
		Component(const GameObject* obj, bool enable = true);

		virtual ~Component();

	protected:
		virtual void Tick(float deltatime);

		virtual void LateTick(float deltatime);

		virtual void OnEnable();

		virtual void OnDisable();


	public:
		// ��������
		const GameObject* gameobject;
		// ���������Transform
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
