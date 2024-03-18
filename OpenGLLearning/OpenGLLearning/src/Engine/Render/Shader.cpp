#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Renderer.h"

#include "Engine/Math/CMatrix.h"


namespace Engine
{
	Shader::Shader(const std::string& filepath)
		: m_FilePath(filepath), m_RendererID(0)
	{
		this->LoadShader(m_FilePath);
	}

	//Shader::Shader() : m_FilePath(""), m_RendererID(0)
	//{

	//}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(this->m_RendererID));
	}

	void Shader::LoadShader(const std::string& filepath)
	{
		ShaderProgramSource source = this->ParseShader(filepath);
		this->m_RendererID = this->CreateShader(source.VertexSource, source.FragmentSource);
	}

	void Shader::Bind() const
	{
		// �� Shader
		glUseProgram(this->m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		GLCall(glUniform1i(this->GetUniformLocation(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float v0)
	{
		GLCall(glUniform1f(this->GetUniformLocation(name), v0));
	}

	void Shader::SetUniform2f(const std::string& name, float v0, float v1)
	{
		GLCall(glUniform2f(this->GetUniformLocation(name), v0, v1));
	}

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		GLCall(glUniform3f(this->GetUniformLocation(name), v0, v1, v2));
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(this->GetUniformLocation(name), v0, v1, v2, v3));
	}

#if USING_GLM
	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
#else
	void Shader::SetUniformMat4f(const std::string& name, const Engine::CMatrix& matrix)
#endif
	{
		GLCall(glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}


	unsigned int Shader::GetUniformLocation(const std::string& name)
	{
		if (this->m_UniformLocationCache.find(name) != this->m_UniformLocationCache.end()) {
			return this->m_UniformLocationCache[name];
		}
		GLCall(int location = glGetUniformLocation(this->m_RendererID, name.c_str()));
		if (location == -1) {
			std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
		}
		this->m_UniformLocationCache[name] = location;
		return location;
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType {
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line, '\r')) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					// set mode to vertex
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					// set mode to fragment
					type = ShaderType::FRAGMENT;
				}
			}
			else if (type != ShaderType::NONE) {
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		// ����һ�� Shader ����
		unsigned int program = glCreateProgram();
		// ���� Vertex
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		// ���� Fragment
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		// Program Attach Shader
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		// Link Program
		glLinkProgram(program);
		// Input Program
		glValidateProgram(program);

		// �Ѵ洢��ʵ�ʵĳ���֮�п��� Delete Shader
		// �����Բ��� Detach, ��Ϊռ��̫С��...
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		// ���� Shader
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		// Shader Դ��(��ɫ��id, Դ������, Դ���ַ���ָ�룬����)
		glShaderSource(id, 1, &src, nullptr);
		// ���� Shader(��ɫ��id)
		glCompileShader(id);

		// error handling

		// glGetShaderiv �� Returns a parameter from a shader object
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		// compile failed
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			// ջ����̬����
			char* message = (char*)_malloca(length * sizeof(char));
			// ��ȡ Shader ��Ϣ(shader id, ��������С, ָ����ʽ��ʵ�ʳ���(�������������?), ������)
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader! " << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}


}

