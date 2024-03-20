#pragma once

#include <GL/glew.h>
#include "Texture.h"

namespace Engine
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture;
	class Material;

#if false
#define ASSERT(x) if(!(x)) __debugbreak();// Only MSVC
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define ASSERT(x) x;
#define GLCall(x) x;
#endif


	void GLClearError();

	bool GLLogCall(const char* function, const char* file, int line);

	class Renderer
	{
	public:
		void Clear() const;

		//void SetClearColor() const;

		void Draw(const VertexArray& va, IndexBuffer& ib, const Shader& shader) const;
		void Draw(const VertexArray& va, IndexBuffer& ib, const Shader& shader, Texture& texture) const;
		void Draw(VertexArray& va, IndexBuffer& ib, Material& material);


		void DrawLines(VertexArray& va, IndexBuffer& ib, Material& material, float lineWidth);

	};


}
