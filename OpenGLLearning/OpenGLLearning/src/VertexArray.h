#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
//class VertextBuffer;
//class VertexBufferLayout;

// ÿһ��������һ������������� => ��һ�£����Կ��ǹ���ͬһ�� VAO
class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	// Use/Bind vb, layout ��Ϊ׼ȷ�������� Add
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

