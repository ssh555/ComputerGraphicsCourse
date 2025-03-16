#pragma once

class Stage;
class ActorController;

namespace Engine
{
	class GameObject;
}

using namespace Engine;

class EntryPoint final
{
public:
	EntryPoint();
	~EntryPoint();

	void Awake();

	void Start();

private:
	Stage* m_stage;
	GameObject* cameraObj;
	GameObject* actorController;
};

