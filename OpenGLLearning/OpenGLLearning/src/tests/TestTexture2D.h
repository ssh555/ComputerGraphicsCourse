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

namespace Render
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture;
	class VertexBuffer;
}
namespace Math
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
		Math::CMatrix m_Proj, m_View;
		Math::CVector m_TranslationA, m_TranslationB;
#endif


		std::unique_ptr<Render::VertexArray> m_VAO;

		std::unique_ptr<Render::VertexBuffer> m_VertexBuffer;

		std::unique_ptr<Render::IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Render::Shader> m_Shader;

		std::unique_ptr<Render::Texture> m_Texture;

	};
}



