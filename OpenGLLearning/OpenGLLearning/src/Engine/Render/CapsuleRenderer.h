#pragma once
#include "MeshRenderer.h"
namespace Engine
{

	class CapsuleRenderer final : public MeshRenderer
	{
	public:
		CapsuleRenderer(GameObject* obj, float radius = 1.0f, float height = 2.0f, unsigned int rings = 20, unsigned int sectors = 20);

		void SetCapsuleMesh(float radius, float height, unsigned int rings, unsigned int sectors);
	};


}
