#include "TestTexture2D.h"

#include "Engine/Render/Renderer.h"
using namespace Engine;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"

#if USING_GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#else
#include "Engine/Math/CMatrix.h"
#include "Engine/Math/CVector.h"
#endif

#include "Engine/Render/VertexBuffer.h"
#include "Engine/Render/VertexBufferLayout.h"
#include "Engine/Render/Texture.h"
#include "Engine/Render/VertexArray.h"
#include "Engine/Render/IndexBuffer.h"
#include "Engine/Render/Shader.h"

#include <iostream>

namespace test
{
	TestTexture2D::TestTexture2D()
		// TODO : 增加Camera脚本 -> 从当前激活(有绘制区域)的Camera获取相关数据
#if USING_GLM
		: m_Proj(glm::ortho(-4.8f, 4.8f, -2.7f, 2.7f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
#else
		: m_Proj(Engine::CMatrix::ortho(-4.8f, 4.8f, -2.7f, 2.7f, -1.0f, 1.0f)),
		m_View(Engine::CMatrix::translate(Engine::CMatrix(1.0f), 0, 0, 0)),
#endif
		m_TranslationA(-0.5f, 0.0f, 0.0f),
		m_TranslationB(0.5f, 0.0f, 0.0f)
	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		m_Texture = std::make_unique<Texture>("res/textures/Circle1.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
		
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0, 0, 0, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->Bind();

		{
#if USING_GLM
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
#else
			Engine::CMatrix model = Engine::CMatrix::translate(Engine::CMatrix(1.0f), m_TranslationA);
			Engine::CMatrix mvp = m_Proj * m_View * model;
#endif

			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
		{
#if USING_GLM
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
#else
			Engine::CMatrix model = Engine::CMatrix::translate(Engine::CMatrix(1.0f), m_TranslationB);
			Engine::CMatrix mvp = m_Proj * m_View * model;
#endif
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -3.0, 3.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, -3.0, 3.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
