#pragma once
#include "MeshRenderer.h"

namespace Engine
{
	class SphereRenderer final : public MeshRenderer
	{
	public:
		SphereRenderer(GameObject* obj, float radius = 0.5f, unsigned int rings = 20, unsigned int sectors = 20);

		void SetSphereMesh(float radius, unsigned int rings, unsigned int sectors);
	};


}
