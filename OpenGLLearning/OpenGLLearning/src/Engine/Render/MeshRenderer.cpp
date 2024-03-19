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

	MeshRenderer::MeshRenderer(GameObject* obj) : Component(obj),
		m_mesh(nullptr), m_mat(nullptr)
	{
		GlobalManager::GetInstance().rendererManager->AlterRendererEnableList(this);
	}

	MeshRenderer::~MeshRenderer()
	{
		IsDelete = true;
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