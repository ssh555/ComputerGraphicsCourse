#include "IndexBuffer.h"

#include "Renderer.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: m_Count(count)
	{
		// ASSERT(ƽ̨����?)
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));

		// ����������(��Ҫ������, ������index)
		GLCall(glGenBuffers(1, &this->m_RendererID));
		// ��ǰѡ�еĻ�����?
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID));
		// ��仺��������(�������ͣ���С��ʵ�����ݣ����Ʒ�ʽ)
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		// ɾ��������
		GLCall(glDeleteBuffers(1, &this->m_RendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID));
	}

	void IndexBuffer::UnBind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}


}
