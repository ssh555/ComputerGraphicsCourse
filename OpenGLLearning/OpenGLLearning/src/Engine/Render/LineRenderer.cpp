#include "LineRenderer.h"
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

	const std::string LineRenderer::PVSTR = "PV";
	const std::string LineRenderer::MODELSTR = "model";
	const std::string LineRenderer::LINECOLOR = "lineColor";

	LineRenderer::LineRenderer(GameObject* obj) : Component(obj, false),
		m_mesh(nullptr), m_mat(LINEMAT)
	{
		GlobalManager::GetInstance().rendererManager->AlterLineRendererEnableList(this);
		m_mat->SetUniform3f(LineRenderer::LINECOLOR, 1.0f, 1.0f, 1.0f);
	}

	LineRenderer::~LineRenderer()
	{
		IsDelete = true;
		delete m_mat;
		delete m_mesh;
	}

	void LineRenderer::Tick(float deltatime)
	{

	}

	void LineRenderer::LateTick(float deltatime)
	{

	}

	void LineRenderer::SetMesh(Mesh* mesh)
	{
		m_mesh = mesh;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_mesh->GetPositions(), m_mesh->GetPositionCount() * sizeof(float));
		VertexBufferLayout layout;

		// ∂•µ„Œª÷√
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(m_mesh->GetIndices(), m_mesh->GetIndexCount());
	}

	const Engine::Mesh* LineRenderer::GetMesh()
	{
		return m_mesh;
	}

	void LineRenderer::SetMaterial(Material* mat)
	{
		m_mat = mat;
	}

	Engine::Material* LineRenderer::GetMaterial()
	{
		return m_mat;
	}

	void LineRenderer::OnEnable()
	{
		GlobalManager::GetInstance().rendererManager->AlterLineRendererEnableList(this);
	}

	void LineRenderer::OnDisable()
	{
		GlobalManager::GetInstance().rendererManager->AlterLineRendererEnableList(this);
	}

	void LineRenderer::Render(const CMatrix& PV, const CVector& viewpoint)
	{
		Renderer renderer;
		m_mat->SetUniformMat4f(PVSTR, PV);
		m_mat->SetUniformMat4f(MODELSTR, transform->GetWorldTransform());

		renderer.DrawLines(*m_VAO, *m_IndexBuffer, *m_mat, this->m_LineWidth);
	}

	Engine::Material* LineRenderer::LINEMAT = nullptr;

}