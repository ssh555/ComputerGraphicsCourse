#pragma once

namespace Render
{
	// 索引缓存
	class IndexBuffer
	{
	private:
		// Internal Renderer ID
		unsigned int m_RendererID;
		// 索引顶点数量
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void UnBind() const;

		inline unsigned int GetCount() const { return this->m_Count; }
	};

}

