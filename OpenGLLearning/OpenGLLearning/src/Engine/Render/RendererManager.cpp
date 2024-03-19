#include "RendererManager.h"
#include "../Global/GlobalManager.h"
#include "../Math/CMatrix.h"
#include "../Camera/Camera.h"
#include "../Component/Transform.h"
#include "MeshRenderer.h"
#include "Texture.h"

namespace Engine
{
	RendererManager::~RendererManager()
	{
		// 释放m_shaderMap中所有Shader对象指针所占用的内存
		for (auto& pair : m_shaderMap)
		{
			delete pair.second; // 删除指针指向的对象
		}
		m_shaderMap.clear(); // 清空unordered_map

		// 不需要，ComponentManager已经delete
		//// 清理其他资源，如果有的话
		//for (auto renderer : m_enabledRenderers)
		//{
		//	if(renderer && !renderer->IsDelete)
		//		delete renderer;
		//}
		//for (auto renderer : m_disabledRenderers)
		//{
		//	if (!renderer->IsDelete)
		//		delete renderer;
		//}
	}

	void RendererManager::RenderAll()
	{
		for (auto camera : GlobalManager::GetInstance().cameraManager->GetSortedCameras())
		{
			if (camera->GetProjectionType() == Camera::ProjectionType::Perspective)
			{
				glEnable(GL_DEPTH_TEST);
				// 设置深度比较函数为小于等于
				glDepthFunc(GL_LEQUAL);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
			CMatrix PV = camera->GetProjectionMatrix() * camera->GetViewMatrix();
			CVector pos = camera->transform->GetWorldPosition();
			
			for (auto renderer : m_enabledRenderers)
			{
				renderer->Render(PV, pos);
			}

		}
	}

	void RendererManager::AlterRendererEnableList(MeshRenderer* renderer)
	{
		auto mgr = GlobalManager::GetInstance().componentManager;
		if (renderer->GetEnable())
		{
			m_disabledRenderers.erase(std::remove(m_disabledRenderers.begin(), m_disabledRenderers.end(), renderer), m_disabledRenderers.end());
			m_enabledRenderers.push_back(renderer);
			mgr->m_enabledComponents.erase(std::remove(mgr->m_enabledComponents.begin(), mgr->m_enabledComponents.end(), renderer), mgr->m_enabledComponents.end());
			mgr->m_disabledComponents.push_back(renderer);
		}
		else
		{
			m_enabledRenderers.erase(std::remove(m_enabledRenderers.begin(), m_enabledRenderers.end(), renderer), m_enabledRenderers.end());
			m_disabledRenderers.push_back(renderer);
		}
	}

	Engine::Shader* RendererManager::GetShader(const std::string& shaderPath)
	{
		auto shaderIt = m_shaderMap.find(shaderPath);
		if (shaderIt == m_shaderMap.end())
		{
			// 如果字典中不存在对应路径的着色器，则创建新的着色器并添加到字典中
			Shader* newShader = new Shader(shaderPath);
			m_shaderMap[shaderPath] = std::move(newShader);
			return m_shaderMap[shaderPath]; // 返回对应路径的着色器的引用
		}
		else
		{
			// 如果字典中存在对应路径的着色器，则直接返回引用
			return shaderIt->second;
		}
	}

	Engine::Texture* RendererManager::GetTexture(const std::string& path)
	{
		auto It = m_TexturesMap.find(path);
		if (It == m_TexturesMap.end())
		{
			// 如果字典中不存在对应路径的着色器，则创建新的着色器并添加到字典中
			Texture* newTex = new Texture(path);
			m_TexturesMap[path] = std::move(newTex);
			return m_TexturesMap[path]; // 返回对应路径的着色器的引用
		}
		else
		{
			// 如果字典中存在对应路径的着色器，则直接返回引用
			return It->second;
		}
	}

}