#pragma once
#include <vector>
namespace Engine
{
	class Camera;
	class CameraManager final
	{
		friend class GlobalManager;
		friend class Camera;

	public:
		void AddCamera(Camera* camera);

		void RemoveCamera(Camera* camera);

		void UpdateAspectRatio(int width, int height);

		const std::vector<Camera*>& GetSortedCameras();

	public:
		int ViewportWidth = 800; // Default viewport width
		int ViewportHeight = 600; // Default viewport height

	private:
		std::vector<Camera*> m_Cameras;
		bool IsSorted = false;

		CameraManager() { }
	};


}
