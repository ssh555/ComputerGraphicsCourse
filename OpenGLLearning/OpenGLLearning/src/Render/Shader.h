#pragma once
#include <string>
#include <unordered_map>

#if USING_GLM
#include "glm/glm.hpp"
#endif


namespace Engine
{
	class CMatrix;
}

namespace Engine
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		std::string m_FilePath;
		unsigned int m_RendererID;
		// caching for uniforms
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		// Set Uniform
		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
#if USING_GLM
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
#else
		void SetUniformMat4f(const std::string& name, const Engine::CMatrix& matrix);
		void SetUniformMat4f(const std::string& name, const Engine::CMatrix& matrix) const;
#endif

	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int GetUniformLocation(const std::string& name);
	};


}
