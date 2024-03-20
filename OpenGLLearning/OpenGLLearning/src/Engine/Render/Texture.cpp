#include "Texture.h"
#include "GL/glew.h"

#include "Renderer.h"
#include "stb_image/stb_image.h"
#include "../Global/GlobalManager.h"


namespace Engine
{
	Texture::Texture(const std::string& path)
		: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
	{
		// OPENGL 从左下角开始，载入时一般会垂直翻转图片
		stbi_set_flip_vertically_on_load(1);
		// 路径，宽，高，BPP，期望的通道数
		this->m_LocalBuffer = stbi_load(path.c_str(), &this->m_Width, &this->m_Height, &this->m_BPP, 4);

		GLCall(glGenTextures(1, &this->m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->m_RendererID));

		// 若不设置，可能会得到黑色的纹理
		// 小于纹理的尺寸，线性重新采样
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		// 大于纹理的尺寸，线性重新采样
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		// 水平方向，限定不会扩大平铺
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		// 垂直方向，限定不会扩大平铺
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


		// 内部格式:处理的格式	格式:提供的格式
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->m_LocalBuffer));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		// 释放缓存数据 =>已经存入 GPU
		if (this->m_LocalBuffer) {
			stbi_image_free(this->m_LocalBuffer);
		}
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &this->m_RendererID));
	}

	void Texture::Bind(unsigned int slot /*= 0*/)
	{
		auto& map = GlobalManager::GetInstance().rendererManager->m_textureIDMap;
		if (map[slot] != this->m_RendererID)
		{
			map[slot] = this->m_RendererID;
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, this->m_RendererID));
		}
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

}
