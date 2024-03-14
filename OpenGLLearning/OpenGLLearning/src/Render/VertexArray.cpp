#include "VertexArray.h"
#include "Renderer.h"

namespace Engine
{
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &this->m_RendererID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &this->m_RendererID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		this->Bind();
		// 使用 vb 指定的顶点缓冲区
		vb.Bind();

		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			// 同一个顶点数组内数据进行编号 => [] => [][]
			// 启用通用顶点数组(顶点数组index)
			GLCall(glEnableVertexAttribArray(i));
			// 定义通用顶点数组(顶点数组index, 顶点size 即几个一组，数据类型， 是否归一化， 顶点间步长， 偏移位置)
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}

	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(this->m_RendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}


}
