#pragma once

#include "Test.h"
#include <memory>
// TODO : Ìæ»»glm¿â
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

namespace Render
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture;
	class VertexBuffer;
}


namespace test
{


	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();


		virtual void OnUpdate(float deltaTime) override;

		virtual void OnRender() override;

		virtual void OnImGuiRender() override;


	private:
		// TODO : Ìæ»»glm¿â
		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

		std::unique_ptr<Render::VertexArray> m_VAO;

		std::unique_ptr<Render::VertexBuffer> m_VertexBuffer;

		std::unique_ptr<Render::IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Render::Shader> m_Shader;

		std::unique_ptr<Render::Texture> m_Texture;

	};
}



