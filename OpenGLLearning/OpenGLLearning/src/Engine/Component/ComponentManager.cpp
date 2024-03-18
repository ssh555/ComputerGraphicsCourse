#include "ComponentManager.h"
#include "Component.h"

namespace Engine
{
	void ComponentManager::SetComponentEnable(Component* component, bool enable)
	{
		if (component->m_enabled != enable)
		{
			component->m_enabled = enable;
			if (enable == true)
			{
				m_disabledComponents.erase(std::remove(m_disabledComponents.begin(), m_disabledComponents.end(), component), m_disabledComponents.end());
				m_enabledComponents.push_back(component);
				component->OnEnable();
			}
			else
			{
				m_enabledComponents.erase(std::remove(m_enabledComponents.begin(), m_enabledComponents.end(), component), m_enabledComponents.end());
				m_disabledComponents.push_back(component);
				component->OnDisable();
			}
		}
	}

	void ComponentManager::TickAll(float deltatime) const
	{
		for (Component* component : m_enabledComponents)
		{
			component->Tick(deltatime);
		}
		for (Component* component : m_enabledComponents)
		{
			component->LateTick(deltatime);
		}
	}

	ComponentManager::ComponentManager()
	{

	}

	ComponentManager::~ComponentManager()
	{

	}

}
