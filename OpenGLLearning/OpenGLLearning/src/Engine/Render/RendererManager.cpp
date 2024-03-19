#include "RendererManager.h"
#include "../Global/GlobalManager.h"
#include "../Math/CMatrix.h"
#include "../Camera/Camera.h"
#include "../Component/Transform.h"
#include "MeshRenderer.h"
#include <algorithm>
#include <execution>
#include <future>

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

		// ����������Դ������еĻ�
		for (auto renderer : m_enabledRenderers)
		{
			delete renderer;
		}
		for (auto renderer : m_disabledRenderers)
		{
			delete renderer;
		}
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
			//// ʹ�ò���forѭ��������Ⱦ
			//std::for_each(std::execution::par, m_enabledRenderers.begin(), m_enabledRenderers.end(),
			//	[&](MeshRenderer* renderer) {
			//		renderer->Render(PV, pos);
			//	});
			
			for (auto renderer : m_enabledRenderers)
			{
				renderer->Render(PV, pos);
			}

			// ����һ�� vector ���洢���е� std::future ����
			//std::vector<std::future<void>> futures;

			//// �ڲ���ѭ�����������񣬲��� std::future ����洢�� vector ��
			//for (auto& renderer : m_enabledRenderers)
			//{
			//	futures.push_back(std::async(std::launch::async, [&](MeshRenderer* renderer) {
			//		renderer->Render(PV, pos);
			//		}, renderer));
			//}

			//// �ȴ������������
			//for (auto& future : futures)
			//{
			//	future.wait();
			//}
		}
	}

	void RendererManager::AlterRendererEnableList(MeshRenderer* renderer)
	{
		if (renderer->GetEnable())
		{
			m_disabledRenderers.erase(std::remove(m_disabledRenderers.begin(), m_disabledRenderers.end(), renderer), m_disabledRenderers.end());
			m_enabledRenderers.push_back(renderer);
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

}