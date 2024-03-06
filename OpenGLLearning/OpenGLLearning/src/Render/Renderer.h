#pragma once

#include <GL/glew.h>

namespace Render
{
	class VertexArray;
	class IndexBuffer;
	class Shader;

#define ASSERT(x) if(!(x)) __debugbreak();// Only MSVC
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))



	void GLClearError();

	bool GLLogCall(const char* function, const char* file, int line);

	class Renderer
	{
	public:
		void Clear() const;

		//void SetClearColor() const;

		void Draw(const VertexArray& va, IndexBuffer& ib, const Shader& shader) const;

	};


}
