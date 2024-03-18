#pragma once
#include <vector>
#include "Shader.h"
#include <unordered_map>

namespace Engine
{
	class MeshRenderer;
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


	private:
		std::unordered_map<std::string, Shader*> m_shaderMap;
		std::vector<MeshRenderer*> m_enabledRenderers;
		std::vector<MeshRenderer*> m_disabledRenderers;
	};
}
