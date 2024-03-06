#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	// 创建缓冲区(需要的数量, 缓冲区index)
	GLCall(glGenBuffers(1, &this->m_RendererID));
	// 当前选中的缓冲区?
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_RendererID));
	// 填充缓冲区数据(数据类型，大小，实际数据，绘制方式)
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	// 删除缓冲区
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
