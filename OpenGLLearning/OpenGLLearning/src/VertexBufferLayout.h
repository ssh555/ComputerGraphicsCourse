#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

// 顶点缓存元素 => 一个顶点
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT:         return 4;
			case GL_UNSIGNED_INT:  return 4;
			case GL_UNSIGNED_BYTE: return 1;
			default:
				ASSERT(false);
				return 0;
		}
	}
};

// 顶点缓存布局
class VertexBufferLayout
{
private:
	// 顶点缓存布局元素
	std::vector<VertexBufferElement> m_Elements;
	// 步长 => 顶点缓存布局的数据长度
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		: m_Stride(0){}

	template<typename T>
	void Push(unsigned int count) 
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) 
	{
		this->m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		// to-do : 乘以 count ?
		this->m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		this->m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		this->m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		this->m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		this->m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	// 顶点缓存布局元素
	inline const std::vector<VertexBufferElement>& GetElements() const { return this->m_Elements; }
	// 步长 => 顶点缓存布局的数据长度
	inline unsigned int GetStride() const { return this->m_Stride; }
};

