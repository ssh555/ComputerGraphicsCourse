#pragma once

namespace Render
{
	// ��������
	class IndexBuffer
	{
	private:
		// Internal Renderer ID
		unsigned int m_RendererID;
		// ������������
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		inline unsigned int GetCount() const { return this->m_Count; }
	};

}

