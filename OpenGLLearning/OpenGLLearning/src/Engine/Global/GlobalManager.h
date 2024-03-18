#pragma once
#include "GLFW/glfw3.h"

#include "../Time/Time.h"
#include "../Component/ComponentManager.h"
#include "../Light/DirectionalLight.h"
#include "../Input/InputManager.h"
#include "../Camera/CameraManager.h"
#include "../Render/RendererManager.h"



namespace Engine
{
	class GlobalManager
	{
		friend class Component;
		friend class Camera;
		friend class RendererManager;
		friend class Material;
		friend class MeshRenderer;

	public:
		static GlobalManager& GetInstance()
		{
			static GlobalManager instance; // 在首次调用时创建唯一的实例
			return instance;
		}

	private:
		ComponentManager* componentManager;

		CameraManager* cameraManager;


		RendererManager* rendererManager;

	public:
		DirectionalLight* globalLight;
		InputManager* inputManager;

		void Init()
		{
			componentManager = new ComponentManager();
			globalLight = new DirectionalLight();
			inputManager = new InputManager();
			cameraManager = new CameraManager();
			rendererManager = new RendererManager();
		}

		void Run()
		{
			// 更新输入

			// 更新物理

			// 更新Tick
			componentManager->TickAll(Time::DeltaTime);

			// 更新Render <- 更新MVP
			rendererManager->RenderAll();

		}

		void windowResizeCallback(GLFWwindow* window, int width, int height) {
			// 设置OpenGL视口的尺寸以匹配新的窗口尺寸
			glViewport(0, 0, width, height);
			cameraManager->UpdateAspectRatio(width, height);
			cameraManager->ViewportWidth = width;
			cameraManager->ViewportHeight = height;
		}

	private:
		// 私有构造函数，防止外部实例化
		GlobalManager()
			: componentManager(nullptr),
			globalLight(nullptr),
			inputManager(nullptr),
			cameraManager(nullptr),
			rendererManager(nullptr)
		{

		}

		~GlobalManager()
		{
			delete componentManager;
			delete globalLight;
			delete inputManager;
			delete cameraManager;
			delete rendererManager;
		}



		// 禁止拷贝构造和赋值操作符，确保只有一个实例
		GlobalManager(const GlobalManager&) = delete;
		GlobalManager& operator=(const GlobalManager&) = delete;
	};


}
