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
	protected:
		virtual void Tick(float deltatime) override;


		virtual void LateTick(float deltatime) override;


		virtual void OnEnable() override;


		virtual void OnDisable() override;

	};


}
