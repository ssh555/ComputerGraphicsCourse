#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
// �ַ�����
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


// TODO : Camera ���� -> ������ͼ�Լ��������
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// ��Ҫ�汾3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// ��Ҫ�汾3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // �� 3.3 �汾
	// ���� OpenGL ����Ϊ ���������ļ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ���� OpenGL ����Ϊ ���������ļ�
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

#pragma region ����
	// ע�ᴰ�ڴ�С�ı��¼��������
	// TODO
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// ��ֱͬ��
	glfwSwapInterval(1);
	// ����֡��
#pragma endregion




	// glew ��ʼ�� : �� glfwMakeContextCurrent ֮��
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// ���������� => glfwTerminate ���ûᵼ�� IndexBuffer ����ջ�ϵĶ����ڴ�,Ȼ�����ִ�н��������~IndexBuffer,��ѭ��glCheckError
	// ���� new �ѷ���,Ȼ���� glfwTerminate ����֮ǰ delete
	{
#pragma region ����
		// ���͸��
/*
	1. ���û��
	2. Set Factor (source, destination) => ��������
	3. Set Equation => ���㹫ʽ(source * factor, destination * factor)
*/
// Ĭ�ϲ�����
		GLCall(glEnable(GL_BLEND));
		// ��� => ��ν������Color�뵱ǰ���ڻ�������Color�������
		// (source = GL_ONE, destination = GL_ZERO) => src �� dest ��������
		// src * src factor, dest * dest factor
		Engine::GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // => (src_alpha, 1 - src_alpha)
		// (mode = GL_FUNC_ADD) => ��ν�������ɫ�����һ��
		// (src * factor [+](mode) dest * factor)
		//GLCall(glBlendEquation())

		// TODO : ˫����Ⱦ
		//glDisable(GL_CULL_FACE);
		// �������޳�
		glEnable(GL_CULL_FACE);
		// ָ��Ҫ�޳�����Ϊ����
		glCullFace(GL_BACK);

		Renderer renderer;

		// glDebugMessageCallback
		// glGetError

		// Setup ImGui binding
		ImGui::CreateContext();
		// SetupStyle
		ImGui::StyleColorsDark();
		// ��ʼ��
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
#pragma endregion

#pragma region TEST����
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

#pragma region ��ѭ��
		// TODO : Add InputManager.InputAction
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			Time::Update();


			GLCall(glClearColor(0, 0, 0, 1));

			/* Render here */
			renderer.Clear();

			//// ������������
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			// ������������
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // ǰ�� ibo �Ѱ�����
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

#pragma region ���߼�
			GlobalManager::GetInstance().Run();
#pragma endregion


#pragma region IMGUI
						// ��ʼһ��ImGui��֡
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

#pragma region ���Ը���
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



			// ����(��Ⱦ) ImGui
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


	// �ر� ImGui
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}



