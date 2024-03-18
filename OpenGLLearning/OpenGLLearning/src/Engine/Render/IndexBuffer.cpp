#include "IndexBuffer.h"

#include "Renderer.h"

namespace Engine
{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: m_Count(count)
	{
		// ASSERT(平台差异?)
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));

		// 创建缓冲区(需要的数量, 缓冲区index)
		GLCall(glGenBuffers(1, &this->m_RendererID));
		// 当前选中的缓冲区?
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID));
		// 填充缓冲区数据(数据类型，大小，实际数据，绘制方式)
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		// 删除缓冲区
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
