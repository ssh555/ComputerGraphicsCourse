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
		Material();

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

		int GetUniform1i(const std::string& name) const;
		float GetUniform1f(const std::string& name) const;
		std::array<float, 2> GetUniform2f(const std::string& name) const;
		std::array<float, 3> GetUniform3f(const std::string& name) const;
		std::array<float, 4> GetUniform4f(const std::string& name) const;
		const Engine::CMatrix& GetUniformMat4f(const std::string& name) const;

		void Bind();
		void Unbind();

	private:
		std::string m_shader;
		std::string m_texturePath;
		Engine::Texture* m_Texture;
		Shader* m_pShader;

		std::unordered_map<std::string, int> m_Uniform1iDict;
		std::unordered_map<std::string, float> m_Uniform1fDict;
		std::unordered_map<std::string, std::array<float, 2>> m_Uniform2fDict;
		std::unordered_map<std::string, std::array<float, 3>> m_Uniform3fDict;
		std::unordered_map<std::string, std::array<float, 4>> m_Uniform4fDict;
		std::unordered_map<std::string, CMatrix> m_UniformMat4fDict;
	};
}
