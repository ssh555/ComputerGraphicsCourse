#pragma once
#include <vector>
#include <unordered_map>

namespace Engine
{
	class MeshRenderer;
	class Texture;
	class Shader;
	class Material;

	class RendererManager
	{
	public:
		static const std::string PVSTR;
		static const  std::string VIEWPOSSTR;
		static const  std::string LIGHTDIRSTR;
		static const  std::string LIGHTCOLOR;

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

		void AlterRendererMaterial(MeshRenderer* renderer, Material* last);

	public:
		std::unordered_map<unsigned int, unsigned int> m_textureIDMap;

	private:
		std::unordered_map<std::string, Shader*> m_shaderMap;
		std::unordered_map<std::string, Texture*> m_TexturesMap;
		std::unordered_map<Material*, std::vector<MeshRenderer*>> m_enablebatchRenderersMap;
		std::vector<MeshRenderer*> m_disabledRenderers;
	};
}
