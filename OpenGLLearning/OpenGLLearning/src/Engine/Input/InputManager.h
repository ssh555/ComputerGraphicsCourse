#pragma once
#include "GLFW/glfw3.h"
#include <functional>
#include <unordered_map>

namespace Engine
{
	class InputManager
	{
		friend class GlobalManager;

	public:
		enum class Key {
			Unknown = -1,
			Space = GLFW_KEY_SPACE,
			Apostrophe = GLFW_KEY_APOSTROPHE,
			Comma = GLFW_KEY_COMMA,
			Minus = GLFW_KEY_MINUS,
			Period = GLFW_KEY_PERIOD,
			Slash = GLFW_KEY_SLASH,
			Num0 = GLFW_KEY_0,
			Num1 = GLFW_KEY_1,
			Num2 = GLFW_KEY_2,
			Num3 = GLFW_KEY_3,
			Num4 = GLFW_KEY_4,
			Num5 = GLFW_KEY_5,
			Num6 = GLFW_KEY_6,
			Num7 = GLFW_KEY_7,
			Num8 = GLFW_KEY_8,
			Num9 = GLFW_KEY_9,
			Semicolon = GLFW_KEY_SEMICOLON,
			Equal = GLFW_KEY_EQUAL,
			A = GLFW_KEY_A,
			B = GLFW_KEY_B,
			C = GLFW_KEY_C,
			D = GLFW_KEY_D,
			E = GLFW_KEY_E,
			F = GLFW_KEY_F,
			G = GLFW_KEY_G,
			H = GLFW_KEY_H,
			I = GLFW_KEY_I,
			J = GLFW_KEY_J,
			K = GLFW_KEY_K,
			L = GLFW_KEY_L,
			M = GLFW_KEY_M,
			N = GLFW_KEY_N,
			O = GLFW_KEY_O,
			P = GLFW_KEY_P,
			Q = GLFW_KEY_Q,
			R = GLFW_KEY_R,
			S = GLFW_KEY_S,
			T = GLFW_KEY_T,
			U = GLFW_KEY_U,
			V = GLFW_KEY_V,
			W = GLFW_KEY_W,
			X = GLFW_KEY_X,
			Y = GLFW_KEY_Y,
			Z = GLFW_KEY_Z,
			LeftBracket = GLFW_KEY_LEFT_BRACKET,
			Backslash = GLFW_KEY_BACKSLASH,
			RightBracket = GLFW_KEY_RIGHT_BRACKET,
			GraveAccent = GLFW_KEY_GRAVE_ACCENT,
			World1 = GLFW_KEY_WORLD_1,
			World2 = GLFW_KEY_WORLD_2,
			Escape = GLFW_KEY_ESCAPE,
			Enter = GLFW_KEY_ENTER,
			Tab = GLFW_KEY_TAB,
			Backspace = GLFW_KEY_BACKSPACE,
			Insert = GLFW_KEY_INSERT,
			Delete = GLFW_KEY_DELETE,
			Right = GLFW_KEY_RIGHT,
			Left = GLFW_KEY_LEFT,
			Down = GLFW_KEY_DOWN,
			Up = GLFW_KEY_UP,
			PageUp = GLFW_KEY_PAGE_UP,
			PageDown = GLFW_KEY_PAGE_DOWN,
			Home = GLFW_KEY_HOME,
			End = GLFW_KEY_END,
			CapsLock = GLFW_KEY_CAPS_LOCK,
			ScrollLock = GLFW_KEY_SCROLL_LOCK,
			NumLock = GLFW_KEY_NUM_LOCK,
			PrintScreen = GLFW_KEY_PRINT_SCREEN,
			Pause = GLFW_KEY_PAUSE,
			F1 = GLFW_KEY_F1,
			F2 = GLFW_KEY_F2,
			F3 = GLFW_KEY_F3,
			F4 = GLFW_KEY_F4,
			F5 = GLFW_KEY_F5,
			F6 = GLFW_KEY_F6,
			F7 = GLFW_KEY_F7,
			F8 = GLFW_KEY_F8,
			F9 = GLFW_KEY_F9,
			F10 = GLFW_KEY_F10,
			F11 = GLFW_KEY_F11,
			F12 = GLFW_KEY_F12,
			F13 = GLFW_KEY_F13,
			F14 = GLFW_KEY_F14,
			F15 = GLFW_KEY_F15,
			F16 = GLFW_KEY_F16,
			F17 = GLFW_KEY_F17,
			F18 = GLFW_KEY_F18,
			F19 = GLFW_KEY_F19,
			F20 = GLFW_KEY_F20,
			F21 = GLFW_KEY_F21,
			F22 = GLFW_KEY_F22,
			F23 = GLFW_KEY_F23,
			F24 = GLFW_KEY_F24,
			F25 = GLFW_KEY_F25,
			NumPad0 = GLFW_KEY_KP_0,
			NumPad1 = GLFW_KEY_KP_1,
			NumPad2 = GLFW_KEY_KP_2,
			NumPad3 = GLFW_KEY_KP_3,
			NumPad4 = GLFW_KEY_KP_4,
			NumPad5 = GLFW_KEY_KP_5,
			NumPad6 = GLFW_KEY_KP_6,
			NumPad7 = GLFW_KEY_KP_7,
			NumPad8 = GLFW_KEY_KP_8,
			NumPad9 = GLFW_KEY_KP_9,
			NumPadDecimal = GLFW_KEY_KP_DECIMAL,
			NumPadDivide = GLFW_KEY_KP_DIVIDE,
			NumPadMultiply = GLFW_KEY_KP_MULTIPLY,
			NumPadSubtract = GLFW_KEY_KP_SUBTRACT,
			NumPadAdd = GLFW_KEY_KP_ADD,
			NumPadEnter = GLFW_KEY_KP_ENTER,
			NumPadEqual = GLFW_KEY_KP_EQUAL,
			LeftShift = GLFW_KEY_LEFT_SHIFT,
			LeftControl = GLFW_KEY_LEFT_CONTROL,
			LeftAlt = GLFW_KEY_LEFT_ALT,
			LeftSuper = GLFW_KEY_LEFT_SUPER,
			RightShift = GLFW_KEY_RIGHT_SHIFT,
			RightControl = GLFW_KEY_RIGHT_CONTROL,
			RightAlt = GLFW_KEY_RIGHT_ALT,
			RightSuper = GLFW_KEY_RIGHT_SUPER,
			Menu = GLFW_KEY_MENU
		};

		enum class KeyAction {
			Press = GLFW_PRESS,
			Release = GLFW_RELEASE,
			Repeat = GLFW_REPEAT
		};

		enum class MouseButton {
			Button1 = GLFW_MOUSE_BUTTON_1,
			Button2 = GLFW_MOUSE_BUTTON_2,
			Button3 = GLFW_MOUSE_BUTTON_3,
			Button4 = GLFW_MOUSE_BUTTON_4,
			Button5 = GLFW_MOUSE_BUTTON_5,
			Button6 = GLFW_MOUSE_BUTTON_6,
			Button7 = GLFW_MOUSE_BUTTON_7,
			Button8 = GLFW_MOUSE_BUTTON_8,
			Left = GLFW_MOUSE_BUTTON_LEFT,
			Right = GLFW_MOUSE_BUTTON_RIGHT,
			Middle = GLFW_MOUSE_BUTTON_MIDDLE
		};

		enum class MouseButtonAction {
			Press = GLFW_PRESS,
			Release = GLFW_RELEASE
		};

		// 事件
		struct Event {
			// 事件类型
			enum class EventType { Key, MouseButton, MouseMove, MouseScroll, WindowResize } type;
			union {
				// 键盘事件 Key
				struct {
					Key key;
					enum class KeyAction keyaction;
				};

				// 鼠标按钮事件 MouseButton
				struct {
					MouseButton button;
					enum class MouseButtonAction mouseaction;
					double xpos;
					double ypos;
				};

				// 鼠标移动事件 MouseMove
				struct {
					double xpos;
					double ypos;
				};

				// 鼠标滚动事件 MouseScroll
				struct {
					double xoffset;
					double yoffset;
				};

				// 窗口大小调整事件 WindowResize
				struct {
					int width;
					int height;
				};
			};
		};

	private:
		InputManager();


	public:
		// 绑定输入事件
		void BindInputAction(GLFWwindow* window);

		// 注册键盘按键事件回调函数
		void RegisterKeyCallback(Key key, std::function<void(Key, KeyAction)> callback);

		// 注册鼠标按钮事件回调函数
		void RegisterMouseButtonCallback(MouseButton button, std::function<void(MouseButton, MouseButtonAction, double, double)> callback);

		// 注册鼠标移动事件回调函数
		void RegisterMouseMoveCallback(std::function<void(double, double)> callback);

		// 注册鼠标滚动事件回调函数
		void RegisterMouseScrollCallback(std::function<void(double, double)> callback);

		// 注册窗口大小调整事件回调函数
		void RegisterWindowResizeCallback(std::function<void(int, int)> callback);


	private:
		GLFWwindow* window;

		// 键盘按键事件回调函数集合
		std::unordered_map<Key, std::function<void(Key, KeyAction)>> keyCallbacks;

		// 鼠标按钮事件回调函数集合
		std::unordered_map<MouseButton, std::function<void(MouseButton, MouseButtonAction, double, double)>> mouseButtonCallbacks;

		// 鼠标移动事件回调函数集合
		std::vector<std::function<void(double, double)>> mouseMoveCallbacks;

		// 鼠标滚动事件回调函数集合
		std::vector<std::function<void(double, double)>> mouseScrollCallbacks;

		// 窗口大小调整事件回调函数集合
		std::vector<std::function<void(int, int)>> windowResizeCallbacks;

		// 触发键盘按键事件
		void TriggerKeyEvent(Key key, KeyAction action);

		// 触发鼠标按钮事件
		void TriggerMouseButtonEvent(MouseButton button, MouseButtonAction action, double xpos, double ypos);

		// 触发鼠标移动事件
		void TriggerMouseMoveEvent(double xpos, double ypos);

		// 触发鼠标滚动事件
		void TriggerMouseScrollEvent(double xoffset, double yoffset);

		// 触发窗口大小调整事件
		void TriggerWindowResizeEvent(int width, int height);
	};
}
