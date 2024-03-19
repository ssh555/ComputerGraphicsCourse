#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>

namespace Engine
{
	class MeshRenderer;
	class Texture;
	class RendererManager
	{
		friend class MeshRenderer;
		friend class GlobalManager;
		friend class Material;

	private:
		RendererManager()
		{

		}

		~RendererManager();

	private:
		void RenderAll();

		void AlterRendererEnableList(MeshRenderer* renderer);

		Shader* GetShader(const std::string& shaderPath);

		Texture* GetTexture(const std::string& path);

	public:
		std::unordered_map<unsigned int, unsigned int> m_textureIDMap;

	private:
		std::unordered_map<std::string, Shader*> m_shaderMap;
		std::unordered_map<std::string, Texture*> m_TexturesMap;
		std::vector<MeshRenderer*> m_enabledRenderers;
		std::vector<MeshRenderer*> m_disabledRenderers;
	};
}
