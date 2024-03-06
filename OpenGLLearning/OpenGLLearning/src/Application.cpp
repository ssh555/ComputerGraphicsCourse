#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
// �ַ�����
#include <sstream>

#include "Render/Renderer.h"
#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Renderer.h"
#include "Render/Texture.h"
using namespace Render;

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "Application.h"
#include "tests/TestTexture2D.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// ����OpenGL�ӿڵĳߴ���ƥ���µĴ��ڳߴ�
	glViewport(0, 0, width, height);
	// TODO : �������� & Camera & Shader
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

	// ע�ᴰ�ڴ�С�ı��¼��������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// ��ֱͬ��
	glfwSwapInterval(1);
	// ����֡��


	// glew ��ʼ�� : �� glfwMakeContextCurrent ֮��
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// ���������� => glfwTerminate ���ûᵼ�� IndexBuffer ����ջ�ϵĶ����ڴ�,Ȼ�����ִ�н��������~IndexBuffer,��ѭ��glCheckError
	// ���� new �ѷ���,Ȼ���� glfwTerminate ����֮ǰ delete
	{
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
		Render::GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // => (src_alpha, 1 - src_alpha)
		// (mode = GL_FUNC_ADD) => ��ν�������ɫ�����һ��
		// (src * factor [+](mode) dest * factor)
		//GLCall(glBlendEquation())


		Render::Renderer renderer;

		// glDebugMessageCallback
		// glGetError

		// Setup ImGui binding
		ImGui::CreateContext();
		// SetupStyle
		ImGui::StyleColorsDark();
		// ��ʼ��
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0, 0, 0, 1));

			/* Render here */
			renderer.Clear();

			//// ������������
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			// ������������
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // ǰ�� ibo �Ѱ�����
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			

			// ��ʼһ��ImGui��֡
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

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

			// ����(��Ⱦ) ImGui
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
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



