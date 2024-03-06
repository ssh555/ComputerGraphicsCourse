#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	// ����������(��Ҫ������, ������index)
	GLCall(glGenBuffers(1, &this->m_RendererID));
	// ��ǰѡ�еĻ�����?
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
	// ��仺��������(�������ͣ���С��ʵ�����ݣ����Ʒ�ʽ)
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	// ɾ��������
	GLCall(glDeleteBuffers(1, &this->m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
}

void VertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
