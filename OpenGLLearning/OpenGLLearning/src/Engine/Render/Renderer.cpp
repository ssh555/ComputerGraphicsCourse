#include "Renderer.h"
#include <iostream>

#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Material.h"
#include "../Math/CMatrix.h"

namespace Engine
{
	GLuint Renderer::transformBuffer = -1;
	unsigned int Renderer::CNT = 0;

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

	Renderer::Renderer()
	{
		++Renderer::CNT;
		if (Renderer::transformBuffer == -1)
		{
			// 生成并绑定变换矩阵缓冲对象
			glGenBuffers(1, &transformBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
			// 在这里填充数据
			glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑
		}
	}

	Renderer::~Renderer()
	{
		--Renderer::CNT;
		if (Renderer::CNT == 0)
		{
			// 删除缓冲对象
			glDeleteBuffers(1, &transformBuffer);
		}
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

	void Renderer::DrawInstanced(VertexArray& va, IndexBuffer& ib, Material& material, const std::vector<CMatrix>& transforms)
	{
		material.Bind();
		va.Bind();
		ib.Bind();
		// 绑定已经创建好的缓冲对象
		glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);

		// 将变换矩阵数组传递到顶点着色器中
		glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(CMatrix), &transforms[0], GL_STATIC_DRAW);

		// 启用实例化属性并设置指针
		for (GLuint i = 0; i < 4; ++i) {
			glEnableVertexAttribArray(3 + i);
			glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(CMatrix), (GLvoid*)(sizeof(GLfloat) * i * 4));
			glVertexAttribDivisor(3 + i, 1); // 每个实例更新一次
		}

		// 绘制所有实例
		glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, transforms.size());

		// 解绑定缓冲对象
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

