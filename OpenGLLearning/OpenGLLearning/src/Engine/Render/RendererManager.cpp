#include "RendererManager.h"
#include "Renderer.h"

#include "../Global/GlobalManager.h"
#include "../Math/CMatrix.h"
#include "../Camera/Camera.h"
#include "../Component/Transform.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"

namespace Engine
{
	const std::string RendererManager::PVSTR = "PV";
	const std::string RendererManager::VIEWPOSSTR = "viewPos";
	const std::string RendererManager::LIGHTDIRSTR = "lightDir";
	const std::string RendererManager::LIGHTCOLOR = "lightColor";

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
			CVector viewpoint = camera->transform->GetWorldPosition();
			Renderer renderer;
			for (auto rendererList : m_enablebatchRenderersMap)
			{
				if (rendererList.second.size() >= 1)
				{
					std::vector<CMatrix> transforms;
					for (auto renderer : rendererList.second)
					{
						transforms.push_back(renderer->gameobject->GetTransform()->GetWorldTransform());
					}
					Material* m_mat = rendererList.first;
					m_mat->SetUniformMat4f(PVSTR, PV);
					m_mat->SetUniform3f(VIEWPOSSTR, viewpoint.x, viewpoint.y, viewpoint.z);
					if (GlobalManager::GetInstance().globalLight->IsDirty)
					{
						auto lightdir = (GlobalManager::GetInstance().globalLight->GetTransform()->GetForward());
						m_mat->SetUniform3f(LIGHTDIRSTR, lightdir.x, lightdir.y, lightdir.z);
						auto color = GlobalManager::GetInstance().globalLight->GetLightColor() * GlobalManager::GetInstance().globalLight->GetIntensity();
						m_mat->SetUniform3f(LIGHTCOLOR, color.x, color.y, color.z);
					}

					auto meshrenderer = rendererList.second[0];
					renderer.DrawInstanced(*meshrenderer->m_VAO, *meshrenderer->m_IndexBuffer, *m_mat, transforms);
				}

			}

		}
	}

	void RendererManager::AlterRendererEnableList(MeshRenderer* renderer)
	{
		if (renderer->GetEnable())
		{
			m_disabledRenderers.erase(std::remove(m_disabledRenderers.begin(), m_disabledRenderers.end(), renderer), m_disabledRenderers.end());
			m_enablebatchRenderersMap[renderer->GetMaterial()].push_back(renderer);
		}
		else
		{
			auto& tmp = m_enablebatchRenderersMap[renderer->GetMaterial()];
			tmp.erase(std::remove(tmp.begin(), tmp.end(), renderer), tmp.end());
			m_disabledRenderers.push_back(renderer);
		}
	}

	void RendererManager::AlterRendererMaterial(MeshRenderer* renderer, Material* last)
	{
		if (renderer->GetEnable())
		{
			auto& tmp = m_enablebatchRenderersMap[last];
			tmp.erase(std::remove(tmp.begin(), tmp.end(), renderer), tmp.end());
			// ��� tmp Ϊ�գ��ʹ� m_enablebatchRenderersMap ���Ƴ���Ӧ����
			if (tmp.empty()) {
				m_enablebatchRenderersMap.erase(last);
			}
			m_enablebatchRenderersMap[renderer->GetMaterial()].push_back(renderer);
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