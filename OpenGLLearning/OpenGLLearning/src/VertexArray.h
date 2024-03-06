#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
//class VertextBuffer;
//class VertexBufferLayout;

// 每一个都生成一个顶点数组对象 => 不一致，可以考虑共用同一个 VAO
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	// Use/Bind vb, layout 更为准确，而不是 Add
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

