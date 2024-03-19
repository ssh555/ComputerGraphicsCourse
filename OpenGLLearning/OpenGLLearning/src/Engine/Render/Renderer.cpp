#include "Renderer.h"
#include <iostream>

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Material.h"

namespace Engine
{
	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError()) {
			std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
			return false;
		}
		return true;
	}

	void Renderer::Clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	}

	void Renderer::Draw(const VertexArray& va, IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Material& material)
	{
		material.Bind();
		va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Renderer::Draw(const VertexArray& va, IndexBuffer& ib, const Shader& shader, Texture& texture) const
	{
		shader.Bind();
		texture.Bind(); // Bind texture
		va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

		// Unbind texture
		texture.Unbind();

	}

}

