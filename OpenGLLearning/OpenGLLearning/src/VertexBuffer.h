#pragma once


// ���㻺��
class VertexBuffer
{
private:
	// Internal Renderer ID
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};

