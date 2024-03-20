#pragma once
#include "../Component/Component.h"
#include <memory>
#include <string>

namespace Engine
{
	class Mesh;
	class Material;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class CMatrix;
	class CVector;


	class LineRenderer : public Component
	{
	public:
		static const std::string PVSTR;
		static const  std::string MODELSTR;
		static const  std::string LINECOLOR;

		friend class GameObject;
		friend class RendererManager;

	protected:
		LineRenderer(GameObject* obj);

		virtual ~LineRenderer();


		virtual void Tick(float deltatime) override;


		virtual void LateTick(float deltatime) override;

	public:
		void SetMesh(Mesh* mesh);

		const Mesh* GetMesh();

		void SetMaterial(Material* mat);

		Material* GetMaterial();

		float m_LineWidth = 1.0f;

	protected:
		void OnEnable() override;

		void OnDisable() override;

	private:
		void Render(const CMatrix& PV, const CVector& viewpoint);

		bool IsDelete = false;

	protected:
		Mesh* m_mesh;
		Material* m_mat;

		std::unique_ptr<Engine::VertexArray> m_VAO;
		std::unique_ptr<Engine::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Engine::IndexBuffer> m_IndexBuffer;

	};


}
