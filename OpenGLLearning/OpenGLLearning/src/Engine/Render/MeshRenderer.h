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

	class MeshRenderer : public Component
	{
	public:
		static const std::string PVSTR;
		static const  std::string MODELSTR;
		static const  std::string VIEWPOSSTR;
		static const  std::string LIGHTDIRSTR;
		static const  std::string LIGHTCOLOR;
		static MeshRenderer* RayCast(const CVector& rayOrigin, const CVector& rayDirection, const float hitDistance);
	private:
		static bool RayTriangleIntersect(const CVector& rayOrigin, const CVector& rayDirection,
			const CVector& v0, const CVector& v1, const CVector& v2,
			float& hitDistance);

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

		bool IsDelete = false;

	public:
		bool bRayCast = false;

	protected:
		Mesh* m_mesh;
		Material* m_mat;

		std::unique_ptr<Engine::VertexArray> m_VAO;
		std::unique_ptr<Engine::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Engine::IndexBuffer> m_IndexBuffer;

	private:

	};

}

