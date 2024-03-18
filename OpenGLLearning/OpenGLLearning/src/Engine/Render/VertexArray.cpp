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
		// ʹ�� vb ָ���Ķ��㻺����
		vb.Bind();

		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			// ͬһ���������������ݽ��б�� => [] => [][]
			// ����ͨ�ö�������(��������index)
			GLCall(glEnableVertexAttribArray(i));
			// ����ͨ�ö�������(��������index, ����size ������һ�飬�������ͣ� �Ƿ��һ���� ����䲽���� ƫ��λ��)
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
