#pragma once

#include "Test.h"
#include <memory>
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

class VertexArray;
class IndexBuffer;
class Shader;
class Texture;
class VertexBuffer;

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
		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;

		std::unique_ptr<VertexArray> m_VAO;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;

		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;

		std::unique_ptr<Texture> m_Texture;

	};
}



