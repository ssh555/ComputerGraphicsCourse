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
			static GlobalManager instance; // ���״ε���ʱ����Ψһ��ʵ��
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
			// ��������

			// ��������

			// ����Tick
			componentManager->TickAll(Time::DeltaTime);

			// ����Render <- ����MVP
			rendererManager->RenderAll();

		}

		void windowResizeCallback(GLFWwindow* window, int width, int height) {
			// ����OpenGL�ӿڵĳߴ���ƥ���µĴ��ڳߴ�
			glViewport(0, 0, width, height);
			cameraManager->UpdateAspectRatio(width, height);
			cameraManager->ViewportWidth = width;
			cameraManager->ViewportHeight = height;
		}

	private:
		// ˽�й��캯������ֹ�ⲿʵ����
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



		// ��ֹ��������͸�ֵ��������ȷ��ֻ��һ��ʵ��
		GlobalManager(const GlobalManager&) = delete;
		GlobalManager& operator=(const GlobalManager&) = delete;
	};


}
