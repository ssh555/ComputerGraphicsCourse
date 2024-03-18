#include "CameraManager.h"
#include "Camera.h"
#include <algorithm>

namespace Engine
{

	void CameraManager::AddCamera(Camera* camera)
	{
		m_Cameras.push_back(std::move(camera));
		IsSorted = false;
	}

	void CameraManager::RemoveCamera(Camera* camera)
	{
		auto it = std::find(m_Cameras.begin(), m_Cameras.end(), camera);
		if (it != m_Cameras.end())
		{
			m_Cameras.erase(it);
			IsSorted = false;
		}
	}

	void CameraManager::UpdateAspectRatio(int width, int height)
	{
		for (auto camera : m_Cameras)
		{
			camera->SetAspectRatio(static_cast<float>(width) / height);
		}
	}

	const std::vector<Camera*>& CameraManager::GetSortedCameras()
	{
		if (IsSorted == false)
		{
			// ¶ÔÉãÏñ»ú°´ÕÕäÖÈ¾Ë³Ðò½øÐÐÅÅÐò
			std::sort(m_Cameras.begin(), m_Cameras.end(), [](const Camera* a, const Camera* b) {
				return a->GetRenderOrder() < b->GetRenderOrder();
				});
			IsSorted = true;
		}
		return m_Cameras;
	}

}