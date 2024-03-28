#pragma once

#include <string>
#include <memory>
#include <array>
#include <unordered_map>

namespace Engine
{
	class Shader;
	class Texture;
	class CMatrix;

	class Material
	{
	public:
		//Material();
		Material(const std::string& shaderpath = "res/shaders/StandardShader.shader", bool IsSetTex = true);

		const std::string& GetShaderResPath() const;
		void SetShader(const std::string& shader);

		Shader* GetShader();

		const std::string& GetTexturePath() const;
		const Engine::Texture& GetTexture() const;

		void SetTexture(const std::string& texturePath);

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const CMatrix& matrix);

		void Bind();
		void Unbind();

	private:
		std::string m_shader;
		std::string m_texturePath;
		Engine::Texture* m_Texture;
		Shader* m_pShader;
	};
}
