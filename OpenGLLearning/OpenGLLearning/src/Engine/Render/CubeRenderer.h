#pragma once
#include "MeshRenderer.h"
namespace Engine
{
	class CubeRenderer : public MeshRenderer
	{
	public:
		CubeRenderer(GameObject* obj);

	private:
		void SetCubeMesh();
	};


}
