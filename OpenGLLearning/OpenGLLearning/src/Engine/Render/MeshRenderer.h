#pragma once
#include "../Component/Component.h"
#include <memory>

namespace Engine
{
	class Mesh;
	class Material;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class CMatrix;
	class CVector;

	class MeshRenderer : public Component
	{
		friend class GameObject;
		friend class RendererManager;

	protected:
		MeshRenderer(GameObject* obj);

		virtual ~MeshRenderer();


		virtual void Tick(float deltatime) override;


		virtual void LateTick(float deltatime) override;

	public:
		void SetMesh(Mesh* mesh);

		const Mesh* GetMesh();

		void SetMaterial(Material* mat);

		Material* GetMaterial();

	protected:
		void OnEnable() override;

		void OnDisable() override;

	private:
		void Render(const CMatrix& PV, const CVector& viewpoint);

	protected:
		Mesh* m_mesh;
		Material* m_mat;

		std::unique_ptr<Engine::VertexArray> m_VAO;
		std::unique_ptr<Engine::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Engine::IndexBuffer> m_IndexBuffer;

	};

}

