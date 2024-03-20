#include "CubeOutlineRenderer.h"
#include "Mesh.h"


namespace Engine
{

	CubeOutlineRenderer::CubeOutlineRenderer(GameObject* obj) : LineRenderer(obj)
	{
		SetCubeOutlineMesh();
	}

	void CubeOutlineRenderer::SetCubeOutlineMesh()
	{
		// 立方体的顶点数据
		float positions[] = {
			// 前面四个顶点
			-0.5f, -0.5f,  0.5f, // 左下 0
			 0.5f, -0.5f,  0.5f, // 右下 1
			 0.5f,  0.5f,  0.5f, // 右上 2
			-0.5f,  0.5f,  0.5f, // 左上 3
			// 后面四个顶点
			 0.5f, -0.5f, -0.5f, // 右下 4
			-0.5f, -0.5f, -0.5f, // 左下 5
			-0.5f,  0.5f, -0.5f, // 左上 6
			 0.5f,  0.5f, -0.5f, // 右上 7
		};

		// 立方体的线索引
		unsigned int indices[] = {
			// 前面
			0, 1, 1, 2, 2, 3, 3, 0,
			// 后面
			4, 5, 5, 6, 6, 7, 7, 4,
			// 连接前后面的线
			0, 5, 1, 4, 2, 7, 3, 6,
		};

		// 创建网格并设置
		Mesh* mesh = new Mesh(positions, sizeof(positions) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
		SetMesh(mesh);
	}


}