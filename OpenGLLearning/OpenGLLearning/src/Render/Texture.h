#pragma once
#include <string>

namespace Render
{
	class Texture
	{
	private:
		unsigned int m_RendererID;
		std::string m_FilePath;
		unsigned char* m_LocalBuffer;
		// 宽，高，实际纹理的每像素位(一个像素包含几个bit)
		int m_Width, m_Height, m_BPP;

	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return this->m_Width; }
		inline int GetHeight() const { return this->m_Height; }
	};


}
