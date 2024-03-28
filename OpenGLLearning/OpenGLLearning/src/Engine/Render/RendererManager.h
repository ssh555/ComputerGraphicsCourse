#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>

namespace Engine
{
	class MeshRenderer;
	class Texture;
	class LineRenderer;

	class RendererManager
	{
		friend class MeshRenderer;
		friend class LineRenderer;
		friend class GlobalManager;
		friend class Material;

	private:
		RendererManager();

		~RendererManager();

	private:
		void RenderAll();

		void AlterRendererEnableList(MeshRenderer* renderer);

		void AlterLineRendererEnableList(LineRenderer* renderer);

		Texture* GetTexture(const std::string& path);

	public:
		std::unordered_map<unsigned int, unsigned int> m_textureIDMap;

	private:
		std::unordered_map<std::string, Texture*> m_TexturesMap;
		std::vector<MeshRenderer*> m_enabledRenderers;
		std::vector<MeshRenderer*> m_disabledRenderers;
		std::vector<LineRenderer*> m_enabledLineRenderers;
		std::vector<LineRenderer*> m_disabledLineRenderers;
	};
}
