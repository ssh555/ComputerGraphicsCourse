#include "MeshRenderer.h"
#include "Material.h"
#include "Renderer.h"
#include "Mesh.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "../Global/GlobalManager.h"
#include "../Component/Transform.h"

namespace Engine
{
	const std::string MeshRenderer::PVSTR = "PV";
	const std::string MeshRenderer::MODELSTR = "model";
	const std::string MeshRenderer::VIEWPOSSTR = "viewPos";
	const std::string MeshRenderer::LIGHTDIRSTR = "lightDir";
	const std::string MeshRenderer::LIGHTCOLOR = "lightColor";

	MeshRenderer* MeshRenderer::RayCast(const CVector& rayOrigin, const CVector& rayDirection, const float hitDistance)
	{
		float nearestHitDistance = std::numeric_limits<float>::max();
		MeshRenderer* nearestHitRenderer = nullptr;
		auto dir = rayDirection.Normalized();

		for (auto& renderer : GlobalManager::GetInstance().rendererManager->m_enabledRenderers)
		{
			// 如果Renderer不可见，则跳过
			if (!renderer->bRayCast)
				continue;
			//if (renderer->gameobject->Name == "A-15")
			//{
			//	float a = 10;
			//	a = 1 + 5;
			//}
			// 获取MeshRenderer的顶点数据和索引数据
			const Mesh* mesh = renderer->GetMesh();
			const float* positions = mesh->GetPositions();
			const unsigned int* indices = mesh->GetIndices();
			unsigned int indexCount = mesh->GetIndexCount();

			// 对于每个三角形进行相交检测
			for (unsigned int i = 0; i < indexCount; i += 3)
			{
				// 获取当前三角形的顶点索引
				unsigned int i0 = indices[i];
				unsigned int i1 = indices[i + 1];
				unsigned int i2 = indices[i + 2];

				// 获取三角形的顶点位置
				int _i0 = i0 * 8;
				int _i1 = i1 * 8;
				int _i2 = i2 * 8;
				CVector v0(positions[_i0], positions[_i0 + 1], positions[_i0 + 2]);
				CVector v1(positions[_i1], positions[_i1 + 1], positions[_i1 + 2]);
				CVector v2(positions[_i2], positions[_i2 + 1], positions[_i2 + 2]);
				auto p = renderer->transform->GetWorldTransform();
				v0 = p.posMul(v0);
				v1 = p.posMul(v1);
				v2 = p.posMul(v2);

				// 进行相交检测，如果相交了，计算交点到射线起点的距离
				float t = hitDistance;
				if (RayTriangleIntersect(rayOrigin, dir, v0, v1, v2, t))
				{
					// 检查是否是最近的交点
					if (t < nearestHitDistance && t < hitDistance)
					{
						nearestHitDistance = t;
						nearestHitRenderer = renderer;
					}
				}
			}
		}

		return nearestHitRenderer;
	}

	bool MeshRenderer::RayTriangleIntersect(const CVector& rayOrigin, const CVector& rayDirection, const CVector& v0, const CVector& v1, const CVector& v2, float& hitDistance)
	{
		CVector edge1 = v1 - v0;
		CVector edge2 = v2 - v0;
		CVector pvec = rayDirection.crossMul(edge2);
		float det = edge1.dotMul(pvec);

		if (det == 0) return false; // Ray and triangle are parallel, no intersection

		float invDet = 1.0f / det;
		CVector tvec = rayOrigin - v0;
		float u = tvec.dotMul(pvec) * invDet;
		if (u < 0 || u > 1) return false;

		CVector qvec = tvec.crossMul(edge1);
		float v = rayDirection.dotMul(qvec) * invDet;
		if (v < 0 || v > 1 || u + v > 1) return false;

		float t = edge2.dotMul(qvec) * invDet;
		if (t < 0 || t > hitDistance) return false; // Intersection is behind the ray or beyond the hit distance

		hitDistance = t;
		return true;
	}

	MeshRenderer::MeshRenderer(GameObject* obj) : Component(obj),
		m_mesh(nullptr), m_mat(nullptr)
	{
		GlobalManager::GetInstance().rendererManager->AlterRendererEnableList(this);
	}

	MeshRenderer::~MeshRenderer()
	{
		IsDelete = true;
		if(!m_mat->IsDeleted)
			delete m_mat;
		delete m_mesh;
	}

	void MeshRenderer::Tick(float deltatime)
	{
	}

	void MeshRenderer::LateTick(float deltatime)
	{
	}

	void MeshRenderer::SetMesh(Mesh* mesh)
	{
		m_mesh = mesh;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_mesh->GetPositions(), m_mesh->GetPositionCount() * sizeof(float));
		VertexBufferLayout layout;

		// 顶点位置
		layout.Push<float>(3);
		// 顶点法线
		layout.Push<float>(3);
		// 纹理坐标
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(m_mesh->GetIndices(), m_mesh->GetIndexCount());
	}

	const Mesh* MeshRenderer::GetMesh()
	{
		return m_mesh;
	}

	void MeshRenderer::SetMaterial(Material* mat)
	{
		m_mat = mat;
	}

	Material* MeshRenderer::GetMaterial()
	{
		return m_mat;
	}

	void MeshRenderer::OnEnable()
	{
		GlobalManager::GetInstance().rendererManager->AlterRendererEnableList(this);
	}

	void MeshRenderer::OnDisable()
	{
		GlobalManager::GetInstance().rendererManager->AlterRendererEnableList(this);
	}

	void MeshRenderer::Render(const CMatrix& PV, const CVector& viewpoint)
	{
		Renderer renderer;
		m_mat->SetUniformMat4f(PVSTR, PV);
		m_mat->SetUniformMat4f(MODELSTR, transform->GetWorldTransform());
		m_mat->SetUniform3f(VIEWPOSSTR, viewpoint.x, viewpoint.y, viewpoint.z);
		if (GlobalManager::GetInstance().globalLight->IsDirty)
		{
			auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());
			m_mat->SetUniform3f(LIGHTDIRSTR, lightdir.x, lightdir.y, lightdir.z);
			auto color = GlobalManager::GetInstance().globalLight->GetLightColor() * GlobalManager::GetInstance().globalLight->GetIntensity();
			m_mat->SetUniform3f(LIGHTCOLOR, color.x, color.y, color.z);
		}


		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_mat);
	}

}