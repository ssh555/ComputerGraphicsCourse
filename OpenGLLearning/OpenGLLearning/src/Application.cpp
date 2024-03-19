#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
// 字符串流
#include <sstream>

#include "Engine/Render/Renderer.h"
#include "Engine/Render/VertexBuffer.h"
#include "Engine/Render/IndexBuffer.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Render/Shader.h"
#include "Engine/Render/Renderer.h"
#include "Engine/Render/Texture.h"
using namespace Engine;

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "Application.h"
#include "tests/TestTexture2D.h"
#include "Homework/EntryPoint.h"

#include "Engine/Global/GlobalManager.h"


void windowResizeCallback(GLFWwindow* window, int width, int height) {
	GlobalManager::GetInstance().windowResizeCallback(window, width, height);
}


// TODO : Camera 管理 -> 用于视图以及相关数据
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// 主要版本3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// 次要版本3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 即 3.3 版本
	// 设置 OpenGL 配置为 核心配置文件
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 设置 OpenGL 配置为 兼容配置文件
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

#pragma region 设置
	// 注册窗口大小改变事件处理程序
	// TODO
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// 垂直同步
	glfwSwapInterval(1);
	// 限制帧率
#pragma endregion




	// glew 初始化 : 在 glfwMakeContextCurrent 之后
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// 限制作用域 => glfwTerminate 调用会导致 IndexBuffer 回收栈上的对象内存,然后程序执行结束后调用~IndexBuffer,死循环glCheckError
	// 或者 new 堆分配,然后在 glfwTerminate 调用之前 delete
	{
#pragma region 设置
		// 混合透明
/*
	1. 启用混合
	2. Set Factor (source, destination) => 乘数因子
	3. Set Equation => 计算公式(source * factor, destination * factor)
*/
// 默认不启用
		GLCall(glEnable(GL_BLEND));
		// 混合 => 如何将输出的Color与当前处于缓冲区的Color结合起来
		// (source = GL_ONE, destination = GL_ZERO) => src 和 dest 计算因子
		// src * src factor, dest * dest factor
		Engine::GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // => (src_alpha, 1 - src_alpha)
		// (mode = GL_FUNC_ADD) => 如何将两种颜色混合在一起
		// (src * factor [+](mode) dest * factor)
		//GLCall(glBlendEquation())

		// TODO : 双面渲染
		//glDisable(GL_CULL_FACE);
		// 启用面剔除
		glEnable(GL_CULL_FACE);
		// 指定要剔除的面为背面
		glCullFace(GL_BACK);

		Renderer renderer;

		// glDebugMessageCallback
		// glGetError

		// Setup ImGui binding
		ImGui::CreateContext();
		// SetupStyle
		ImGui::StyleColorsDark();
		// 初始化
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
#pragma endregion

#pragma region TEST设置
		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		//testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		//testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
#pragma endregion

		glfwSetFramebufferSizeCallback(window, windowResizeCallback);

		GlobalManager::GetInstance().Init();
		//GlobalManager::GetInstance().inputManager->BindInputAction(window);
		EntryPoint entrypoint;
		entrypoint.Awake();
		entrypoint.Start();

#pragma region 主循环
		// TODO : Add InputManager.InputAction
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			Time::Update();


			GLCall(glClearColor(0, 0, 0, 1));

			/* Render here */
			renderer.Clear();

			//// 无索引缓冲区
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			// 有索引缓冲区
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // 前面 ibo 已绑定索引
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

#pragma region 主逻辑
			GlobalManager::GetInstance().Run();
#pragma endregion


#pragma region IMGUI
						// 开始一个ImGui新帧
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

#pragma region 测试更新
			if (currentTest)
			{
				currentTest->OnUpdate(0);
				currentTest->OnRender();
				ImGui::Begin("test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}
#pragma endregion



			// 绘制(渲染) ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#pragma endregion



			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

#pragma endregion

		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}


	// 关闭 ImGui
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}



