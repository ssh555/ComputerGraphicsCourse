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
			// ���ɲ��󶨱任���󻺳����
			glGenBuffers(1, &transformBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
			// �������������
			glBindBuffer(GL_ARRAY_BUFFER, 0); // ���
		}
	}

	Renderer::~Renderer()
	{
		--Renderer::CNT;
		if (Renderer::CNT == 0)
		{
			// ɾ���������
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
		// ���Ѿ������õĻ������
		glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);

		// ���任�������鴫�ݵ�������ɫ����
		glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(CMatrix), &transforms[0], GL_STATIC_DRAW);

		// ����ʵ�������Բ�����ָ��
		for (GLuint i = 0; i < 4; ++i) {
			glEnableVertexAttribArray(3 + i);
			glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(CMatrix), (GLvoid*)(sizeof(GLfloat) * i * 4));
			glVertexAttribDivisor(3 + i, 1); // ÿ��ʵ������һ��
		}

		// ��������ʵ��
		glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, transforms.size());

		// ��󶨻������
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

