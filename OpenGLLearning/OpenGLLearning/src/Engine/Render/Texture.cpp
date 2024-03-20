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
		// OPENGL �����½ǿ�ʼ������ʱһ��ᴹֱ��תͼƬ
		stbi_set_flip_vertically_on_load(1);
		// ·�������ߣ�BPP��������ͨ����
		this->m_LocalBuffer = stbi_load(path.c_str(), &this->m_Width, &this->m_Height, &this->m_BPP, 4);

		GLCall(glGenTextures(1, &this->m_RendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, this->m_RendererID));

		// �������ã����ܻ�õ���ɫ������
		// С������ĳߴ磬�������²���
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		// ��������ĳߴ磬�������²���
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		// ˮƽ�����޶���������ƽ��
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		// ��ֱ�����޶���������ƽ��
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));


		// �ڲ���ʽ:����ĸ�ʽ	��ʽ:�ṩ�ĸ�ʽ
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->m_LocalBuffer));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		// �ͷŻ������� =>�Ѿ����� GPU
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
