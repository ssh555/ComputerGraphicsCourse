#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "../Math/CMatrix.h"
#include "../Global/GlobalManager.h"
#include "RendererManager.h"

namespace Engine
{

	Material::Material()
		: m_shader("res/shaders/StandardShader.shader"),
		m_texturePath("res/textures/default_texture.png"),
		m_Texture(std::make_unique<Engine::Texture>(m_texturePath))
	{

	}

	const std::string& Material::GetShaderResPath() const
	{
		return m_shader;
	}

	void Material::SetShader(const std::string shader)
	{
		// 清空存储的值
		m_Uniform1iDict.clear();
		m_Uniform1fDict.clear();
		m_Uniform2fDict.clear();
		m_Uniform3fDict.clear();
		m_Uniform4fDict.clear();
		m_UniformMat4fDict.clear();

		// 更换 Shader
		m_shader = shader;
	}

	Engine::Shader* Material::GetShader() 
	{
		return GlobalManager::GetInstance().rendererManager->GetShader(m_shader);
	}

	const std::string& Material::GetTexturePath() const
	{
		return m_texturePath;
	}

	const std::unique_ptr<Engine::Texture>& Material::GetTexture() const
	{
		return m_Texture;
	}

	void Material::SetTexture(const std::string& texturePath)
	{
		m_Texture = std::make_unique<Engine::Texture>(texturePath);
		m_texturePath = texturePath;
	}

	void Material::SetUniform1i(const std::string& name, int value)
	{
		m_Uniform1iDict[name] = value;
	}

	void Material::SetUniform1f(const std::string& name, float v0)
	{
		m_Uniform1fDict[name] = v0;
	}

	void Material::SetUniform2f(const std::string& name, float v0, float v1)
	{
		m_Uniform2fDict[name] = { v0, v1 };
	}

	void Material::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		m_Uniform3fDict[name] = { v0, v1, v2 };
	}

	void Material::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		m_Uniform4fDict[name] = { v0, v1, v2, v3 };
	}

	void Material::SetUniformMat4f(const std::string& name, const CMatrix& matrix)
	{
		m_UniformMat4fDict[name] = matrix;
	}

	int Material::GetUniform1i(const std::string& name) const
	{
		auto it = m_Uniform1iDict.find(name);
		if (it != m_Uniform1iDict.end()) {
			return it->second;
		}
		// 如果键不存在，可以选择返回一个默认值，或者抛出异常，这里选择返回 0
		return 0;
	}

	float Material::GetUniform1f(const std::string& name) const
	{
		auto it = m_Uniform1fDict.find(name);
		if (it != m_Uniform1fDict.end()) {
			return it->second;
		}
		// 返回默认值 0.0f
		return 0.0f;
	}

	std::array<float, 2> Material::GetUniform2f(const std::string& name) const
	{
		auto it = m_Uniform2fDict.find(name);
		if (it != m_Uniform2fDict.end()) {
			return it->second;
		}
		// 返回默认值 {0.0f, 0.0f}
		return { 0.0f, 0.0f };
	}

	std::array<float, 3> Material::GetUniform3f(const std::string& name) const
	{
		auto it = m_Uniform3fDict.find(name);
		if (it != m_Uniform3fDict.end()) {
			return it->second;
		}
		// 返回默认值 {0.0f, 0.0f, 0.0f}
		return { 0.0f, 0.0f, 0.0f };
	}

	std::array<float, 4> Material::GetUniform4f(const std::string& name) const
	{
		auto it = m_Uniform4fDict.find(name);
		if (it != m_Uniform4fDict.end()) {
			return it->second;
		}
		// 返回默认值 {0.0f, 0.0f, 0.0f, 0.0f}
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	const Engine::CMatrix& Material::GetUniformMat4f(const std::string& name) const
	{
		static const CMatrix identityMatrix(1); // 如果键不存在，返回一个默认的单位矩阵
		auto it = m_UniformMat4fDict.find(name);
		if (it != m_UniformMat4fDict.end()) {
			return it->second;
		}
		// 返回默认的单位矩阵
		return identityMatrix;
	}

	void Material::Bind()
	{
		m_Texture->Bind();

		Shader* shader = GetShader();
		// 绑定 Shader
		shader->Bind();

		shader->SetUniform1i("textureDiffuse", 0); // 假设纹理单元为0
		// 设置 uniform 值
		for (const auto& pair : m_Uniform1iDict) {
			shader->SetUniform1i(pair.first, pair.second);
		}

		for (const auto& pair : m_Uniform1fDict) {
			shader->SetUniform1f(pair.first, pair.second);
		}

		for (const auto& pair : m_Uniform2fDict) {
			const auto& value = pair.second;
			shader->SetUniform2f(pair.first, value[0], value[1]);
		}

		for (const auto& pair : m_Uniform3fDict) {
			const auto& value = pair.second;
			shader->SetUniform3f(pair.first, value[0], value[1], value[2]);
		}

		for (const auto& pair : m_Uniform4fDict) {
			const auto& value = pair.second;
			shader->SetUniform4f(pair.first, value[0], value[1], value[2], value[3]);
		}

		for (const auto& pair : m_UniformMat4fDict) {
			shader->SetUniformMat4f(pair.first, pair.second);
		}

	}

	void Material::Unbind()
	{
		Shader* shader = GetShader();
		shader->Unbind();
	}

}
