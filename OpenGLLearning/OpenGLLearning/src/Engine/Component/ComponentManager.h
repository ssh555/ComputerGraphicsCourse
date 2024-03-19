#pragma once
#include <vector>

namespace Engine
{
	class Component;
	class ComponentManager final
	{
		friend class Component;
		friend class GlobalManager;
		friend class RendererManager;

	private:
		ComponentManager();
		~ComponentManager();

	private:
		// 更改Component的队列
		void SetComponentEnable(Component* component, bool enable);

		void RemoveComponent(Component* component);

		void TickAll(float deltatime) const;


	private:
		std::vector<Component*> m_enabledComponents;
		std::vector<Component*> m_disabledComponents;
	};


}
