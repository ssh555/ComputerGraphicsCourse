#include "Component.h"
#include "../GameObject/GameObject.h"
#include "../Global/GlobalManager.h"


namespace Engine
{
	Component::Component(GameObject* obj, bool enable /*= true*/)
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
		GlobalManager::GetInstance().componentManager->RemoveComponent(this);
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



}
