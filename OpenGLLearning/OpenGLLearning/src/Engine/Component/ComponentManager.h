#pragma once
#include <vector>

namespace Engine
{
	class Component;
	class ComponentManager final
	{
		friend class Component;
		friend class GlobalManager;

	private:
		ComponentManager();
		~ComponentManager();

	private:
		// ����Component�Ķ���
		void SetComponentEnable(Component* component, bool enable);


		void TickAll(float deltatime) const;


	private:
		std::vector<Component*> m_enabledComponents;
		std::vector<Component*> m_disabledComponents;
	};


}