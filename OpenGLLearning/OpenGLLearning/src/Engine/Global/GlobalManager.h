#pragma once
#include "GLFW/glfw3.h"

#include "../Time/Time.h"
#include "../Component/ComponentManager.h"
#include "../Light/DirectionalLight.h"
#include "../Input/InputManager.h"
#include "../Camera/CameraManager.h"
#include "../Render/RendererManager.h"
#include "tests/Test.h"
#include "../GameObjectManager.h"



namespace Engine
{
	class GlobalManager
	{
		friend class Component;
		friend class Camera;
		friend class RendererManager;
		friend class Material;
		friend class MeshRenderer;
		friend class LineRenderer;
		friend class Texture;
		friend class GameObject;

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

		GameObjectManager* gameObjectManager;

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
			gameObjectManager = new GameObjectManager();
		}

		void Run()
		{
			// 更新输入

			// 更新物理

			// 更新Tick
			componentManager->TickAll(Time::DeltaTime);

			// 更新Render <- 更新MVP
			rendererManager->RenderAll();

			gameObjectManager->UpdateActive();

			globalLight->IsDirty = false;
		}

		void windowResizeCallback(GLFWwindow* window, int width, int height) {
			// 设置OpenGL视口的尺寸以匹配新的窗口尺寸
			glViewport(0, 0, width, height);
			cameraManager->UpdateAspectRatio(width, height);
			cameraManager->ViewportWidth = width;
			cameraManager->ViewportHeight = height;
		}

		void GetViewPortSize(int& width, int& height)
		{
			width = cameraManager->ViewportWidth;
			height = cameraManager->ViewportHeight;
		}

		Camera* GetCamera(int index = 0)
		{
			return cameraManager->m_Cameras[index];
		}

	private:
		// 私有构造函数，防止外部实例化
		GlobalManager()
			: componentManager(nullptr),
			globalLight(nullptr),
			inputManager(nullptr),
			cameraManager(nullptr),
			rendererManager(nullptr),
			gameObjectManager(nullptr)
		{
			currentTest = nullptr;
			testMenu = new test::TestMenu(currentTest);
			currentTest = testMenu;
		}

		~GlobalManager()
		{
			delete componentManager;
			delete globalLight;
			delete inputManager;
			delete cameraManager;
			delete rendererManager;
			delete gameObjectManager;
			//delete testMenu;
		}



		// 禁止拷贝构造和赋值操作符，确保只有一个实例
		GlobalManager(const GlobalManager&) = delete;
		GlobalManager& operator=(const GlobalManager&) = delete;

		// TEST

	public:
		test::Test* currentTest;
		test::TestMenu* testMenu;
	};


}
