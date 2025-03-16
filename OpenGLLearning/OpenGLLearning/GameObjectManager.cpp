#include "GameObjectManager.h"
#include "Engine/GameObject/GameObject.h"

Engine::GameObjectManager::GameObjectManager()
{

}

Engine::GameObjectManager::~GameObjectManager()
{
	for (auto go : this->m_gameobjects)
	{
		if (!go->IsDelete)
		{
			delete go;
		}
	}
}

void Engine::GameObjectManager::UpdateActive()
{
	for (auto go : this->m_activegameobjects)
	{
		go->m_active = go->m_tmpactive;
	}
	this->m_activegameobjects.clear();
}
