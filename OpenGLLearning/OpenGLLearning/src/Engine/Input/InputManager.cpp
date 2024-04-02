#include "InputManager.h"
#include "../Global/GlobalManager.h"
#include "../Time/Time.h"
#include <iostream>

namespace Engine
{
	InputManager::InputManager()
		: window(nullptr)
	{

	}

	void InputManager::BindInputAction(GLFWwindow* window)
	{
		this->window = window;
		// 设置键盘按下事件回调函数
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			GlobalManager::GetInstance().inputManager->TriggerKeyEvent(static_cast<Key>(key), static_cast<KeyAction>(action));
			if (static_cast<KeyAction>(action) == KeyAction::Press)
			{
				GlobalManager::GetInstance().inputManager->keyStates[static_cast<Key>(key)].pressFrame = Time::frameCount + 1;
			}
			else if (static_cast<KeyAction>(action) == KeyAction::Release)
			{
				GlobalManager::GetInstance().inputManager->keyStates[static_cast<Key>(key)].releaseFrame = Time::frameCount + 1;
			}
			});

		// 设置鼠标按钮事件回调函数
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			GlobalManager::GetInstance().inputManager->TriggerMouseButtonEvent(static_cast<MouseButton>(button), static_cast<MouseButtonAction>(action), xpos, ypos);
			if (static_cast<KeyAction>(action) == KeyAction::Press)
			{
				GlobalManager::GetInstance().inputManager->keyStates[static_cast<Key>(button)].pressFrame = Time::frameCount + 1;
			}
			else if (static_cast<KeyAction>(action) == KeyAction::Release)
			{
				GlobalManager::GetInstance().inputManager->keyStates[static_cast<Key>(button)].releaseFrame = Time::frameCount + 1;
			}
			});

		// 设置鼠标移动事件回调函数
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
			GlobalManager::GetInstance().inputManager->TriggerMouseMoveEvent(xpos, ypos);
			auto mgr = GlobalManager::GetInstance().inputManager;
			mgr->MouseXOff = (float)xpos - mgr->lastMouseX;
			mgr->MouseYOff = (float)ypos - mgr->lastMouseY;
			mgr->lastMouseX = xpos;
			mgr->lastMouseY = ypos;
			});

		// 设置鼠标滚动事件回调函数
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			GlobalManager::GetInstance().inputManager->TriggerMouseScrollEvent(xoffset, yoffset);
			});

		// 设置窗口大小调整事件回调函数
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			GlobalManager::GetInstance().inputManager->TriggerWindowResizeEvent(width, height);
			});
	}

	void InputManager::RegisterKeyCallback(Key key, std::function<void(Key, KeyAction)> callback)
	{
		keyCallbacks[key] = callback;
	}

	void InputManager::RegisterMouseButtonCallback(MouseButton button, std::function<void(MouseButton, MouseButtonAction, double, double)> callback)
	{
		mouseButtonCallbacks[button] = callback;
	}

	void InputManager::RegisterMouseMoveCallback(std::function<void(double, double)> callback)
	{
		mouseMoveCallbacks.push_back(callback);
	}

	void InputManager::RegisterMouseScrollCallback(std::function<void(double, double)> callback)
	{
		mouseScrollCallbacks.push_back(callback);
	}

	void InputManager::RegisterWindowResizeCallback(std::function<void(int, int)> callback)
	{
		windowResizeCallbacks.push_back(callback);
	}

	bool InputManager::GetKey(Key key)
	{
		auto& state = this->keyStates[key];
		return (state.releaseFrame < state.pressFrame);
	}

	bool InputManager::GetKeyUp(Key key)
	{
		auto& state = this->keyStates[key];
		return (state.releaseFrame == Time::frameCount);
	}

	bool InputManager::GetKeyDown(Key key)
	{
		auto& state = this->keyStates[key];
		return (state.pressFrame == Time::frameCount);
	}

	void InputManager::GetMouseOffset(float& xoff, float& yoff)
	{
		xoff = MouseXOff;
		yoff = MouseYOff;
	}

	void InputManager::TriggerMouseButtonEvent(MouseButton button, MouseButtonAction action, double xpos, double ypos)
	{
		if (mouseButtonCallbacks.find(button) != mouseButtonCallbacks.end())
		{
			mouseButtonCallbacks[button](button, action, xpos, ypos);
		}
	}

	void InputManager::TriggerMouseMoveEvent(double xpos, double ypos)
	{
		for (auto& callback : mouseMoveCallbacks)
		{
			callback(xpos, ypos);
		}
	}

	void InputManager::TriggerMouseScrollEvent(double xoffset, double yoffset)
	{
		for (auto& callback : mouseScrollCallbacks)
		{
			callback(xoffset, yoffset);
		}
	}

	void InputManager::TriggerWindowResizeEvent(int width, int height)
	{
		for (auto& callback : windowResizeCallbacks)
		{
			callback(width, height);
		}
	}

	void InputManager::TriggerKeyEvent(Key key, KeyAction action)
	{
		if (keyCallbacks.find(key) != keyCallbacks.end())
		{
			keyCallbacks[key](key, action);
		}
	}

}