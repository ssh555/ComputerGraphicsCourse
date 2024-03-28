#include "RendererManager.h"
#include "../Global/GlobalManager.h"
#include "../Math/CMatrix.h"
#include "../Camera/Camera.h"
#include "../Component/Transform.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "LineRenderer.h"
#include "Material.h"

namespace Engine
{

	RendererManager::RendererManager()
	{
		LineRenderer::LINEMAT = new Material("res/shaders/LineShader.shader", false);
	}

	RendererManager::~RendererManager()
	{
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
			for (auto renderer : m_enabledLineRenderers)
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

	void RendererManager::AlterLineRendererEnableList(LineRenderer* renderer)
	{
		auto mgr = GlobalManager::GetInstance().componentManager;
		if (renderer->GetEnable())
		{
			m_disabledLineRenderers.erase(std::remove(m_disabledLineRenderers.begin(), m_disabledLineRenderers.end(), renderer), m_disabledLineRenderers.end());
			m_enabledLineRenderers.push_back(renderer);
			mgr->m_enabledComponents.erase(std::remove(mgr->m_enabledComponents.begin(), mgr->m_enabledComponents.end(), renderer), mgr->m_enabledComponents.end());
			mgr->m_disabledComponents.push_back(renderer);
		}
		else
		{
			m_enabledLineRenderers.erase(std::remove(m_enabledLineRenderers.begin(), m_enabledLineRenderers.end(), renderer), m_enabledLineRenderers.end());
			m_disabledLineRenderers.push_back(renderer);
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