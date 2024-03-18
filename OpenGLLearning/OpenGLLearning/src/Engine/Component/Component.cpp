#include "Component.h"
#include "../GameObject/GameObject.h"
#include "../Global/GlobalManager.h"


namespace Engine
{
	Component::Component(const GameObject* obj, bool enable /*= true*/)
		: gameobject(obj), transform(obj->transform), m_enabled(enable)
	{
		if (m_enabled)
		{
			GlobalManager::GetInstance().componentManager->m_enabledComponents.push_back(this);
;		}
		else
		{
			GlobalManager::GetInstance().componentManager->m_disabledComponents.push_back(this);
		}
	}

	Component::~Component()
	{

	}

	void Component::Tick(float deltatime)
	{

	}

	void Component::LateTick(float deltatime)
	{

	}

	void Component::OnEnable()
	{

	}

	void Component::OnDisable()
	{

	}

	void Component::SetEnable(bool enable)
	{
		GlobalManager::GetInstance().componentManager->SetComponentEnable(this, enable);
	}

	bool Component::GetEnable()
	{
		return m_enabled;
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	std::vector<T*>
	Component::GetComponentsInParent()
	{
		return this->gameobject->GetComponentsInParent<T>();
	}

	template <typename T, typename /*= std::enable_if_t<std::is_base_of<Component, T>::value>*/>
	T& Component::GetComponentInParent()
	{
		this->gameobject->GetComponentInParent<T>();
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
