#pragma once
#include <vector>

namespace Engine
{
	class GameObject;
	class GameObjectManager
	{
		friend class GlobalManager;
		friend class GameObject;
	private:
		GameObjectManager();
		~GameObjectManager();

	private:

		void UpdateActive();


	private:
		std::vector<GameObject*> m_gameobjects;
		std::vector<GameObject*> m_activegameobjects;
	};

}

