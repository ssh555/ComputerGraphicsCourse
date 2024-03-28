#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "../Math/CMatrix.h"
#include "../Global/GlobalManager.h"
#include "RendererManager.h"
#include "../Component/Transform.h"
#include <Engine/Render/MeshRenderer.h>

namespace Engine
{

	Material::Material(const std::string& shaderpath /*= "res/shaders/StandardShader.shader"*/, bool IsSetTex)
		: m_shader(shaderpath),
		m_texturePath("res/textures/default_texture.png"),
		m_pShader(nullptr),
		m_Texture(nullptr)
	{
		this->SetShader(m_shader);
		if (IsSetTex)
		{
			this->SetTexture(m_texturePath);
		}
	}

	const std::string& Material::GetShaderResPath() const
	{
		return m_shader;
	}

	void Material::SetShader(const std::string& shader)
	{
		// 更换 Shader
		m_shader = shader;
		if (m_pShader)
		{
			delete m_pShader;
		}
		m_pShader = new Shader(m_shader);
		m_pShader->SetUniform1i("textureDiffuse", 0); // 假设纹理单元为0
	}

	Shader* Material::GetShader()
	{
		if (!m_pShader)
			m_pShader = new Shader(m_shader);
		return m_pShader;
	}

	const std::string& Material::GetTexturePath() const
	{
		return m_texturePath;
	}

	const Engine::Texture& Material::GetTexture() const
	{
		return *m_Texture;
	}

	void Material::SetTexture(const std::string& texturePath)
	{
		m_Texture = GlobalManager::GetInstance().rendererManager->GetTexture(m_texturePath);
		m_texturePath = texturePath;
		this->SetUniform1i("textureDiffuse", 0);
	}

	void Material::SetUniform1i(const std::string& name, int value)
	{
		m_pShader->Bind();
		m_pShader->SetUniform1i(name, value);
	}

	void Material::SetUniform1f(const std::string& name, float v0)
	{
		m_pShader->Bind();
		m_pShader->SetUniform1f(name, v0);
	}

	void Material::SetUniform2f(const std::string& name, float v0, float v1)
	{
		m_pShader->Bind();
		m_pShader->SetUniform2f(name, v0, v1);
	}

	void Material::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		m_pShader->Bind();
		m_pShader->SetUniform3f(name, v0, v1, v2);
	}

	void Material::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		m_pShader->Bind();
		m_pShader->SetUniform4f(name, v0, v1, v2, v3);
	}

	void Material::SetUniformMat4f(const std::string& name, const CMatrix& matrix)
	{
		m_pShader->Bind();
		m_pShader->SetUniformMat4f(name, matrix);
	}
	
	void Material::Bind()
	{
		m_Texture->Bind();
		// 绑定 Shader
		m_pShader->Bind();
	}

	void Material::Unbind()
	{
		Shader* shader = GetShader();
		shader->Unbind();
	}
}
