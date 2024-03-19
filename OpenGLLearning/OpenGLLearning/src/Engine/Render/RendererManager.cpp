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
		// �ͷ�m_shaderMap������Shader����ָ����ռ�õ��ڴ�
		for (auto& pair : m_shaderMap)
		{
			delete pair.second; // ɾ��ָ��ָ��Ķ���
		}
		m_shaderMap.clear(); // ���unordered_map

		// ����Ҫ��ComponentManager�Ѿ�delete
		//// ����������Դ������еĻ�
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
				// ������ȱȽϺ���ΪС�ڵ���
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
			// ����ֵ��в����ڶ�Ӧ·������ɫ�����򴴽��µ���ɫ������ӵ��ֵ���
			Shader* newShader = new Shader(shaderPath);
			m_shaderMap[shaderPath] = std::move(newShader);
			return m_shaderMap[shaderPath]; // ���ض�Ӧ·������ɫ��������
		}
		else
		{
			// ����ֵ��д��ڶ�Ӧ·������ɫ������ֱ�ӷ�������
			return shaderIt->second;
		}
	}

	Engine::Texture* RendererManager::GetTexture(const std::string& path)
	{
		auto It = m_TexturesMap.find(path);
		if (It == m_TexturesMap.end())
		{
			// ����ֵ��в����ڶ�Ӧ·������ɫ�����򴴽��µ���ɫ������ӵ��ֵ���
			Texture* newTex = new Texture(path);
			m_TexturesMap[path] = std::move(newTex);
			return m_TexturesMap[path]; // ���ض�Ӧ·������ɫ��������
		}
		else
		{
			// ����ֵ��д��ڶ�Ӧ·������ɫ������ֱ�ӷ�������
			return It->second;
		}
	}

}