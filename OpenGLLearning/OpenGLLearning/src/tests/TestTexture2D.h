#pragma once

#include "Test.h"
#include <memory>

#if USING_GLM
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#else
#include "Math/CMatrix.h"
#include "Math/CVector.h"
#endif

namespace Engine
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture;
	class VertexBuffer;
}
namespace Engine
{
	class CMatrix;
	class CVector;
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
#if USING_GLM
		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
#else
		Engine::CMatrix m_Proj, m_View;
		Engine::CVector m_TranslationA, m_TranslationB;
#endif


		std::unique_ptr<Engine::VertexArray> m_VAO;

		std::unique_ptr<Engine::VertexBuffer> m_VertexBuffer;

		std::unique_ptr<Engine::IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Engine::Shader> m_Shader;

		std::unique_ptr<Engine::Texture> m_Texture;

	};
}



