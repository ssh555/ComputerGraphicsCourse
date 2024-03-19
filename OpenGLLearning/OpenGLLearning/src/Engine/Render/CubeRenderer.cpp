#include "CubeRenderer.h"
#include "Material.h"
#include "Mesh.h"

namespace Engine
{
	CubeRenderer::CubeRenderer(GameObject* obj) : MeshRenderer(obj)
	{
		SetCubeMesh();

		m_mat = new Material();

		m_mat->SetUniform1f("ambientStrength", 0.6f);
		m_mat->SetUniform1f("specularStrength", 0.5);
		m_mat->SetUniform1f("shininess", 1);
	}

	void CubeRenderer::SetCubeMesh()
	{
		// 更新顶点数据以包含法线和纹理坐标
		float positions[] = {
			// 顶点位置            // 顶点法线          // 纹理坐标
			// 前面（z = 0）
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // 左下
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // 右下
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // 右上
			-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // 左上
			// 后面（z = 1）
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // 右下
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // 左下
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // 左上
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // 右上
			// 顶面（y = 1）
			-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // 左上
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // 右上
			 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // 右下
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, // 左下
			// 底面（y = -1）
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // 左下
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // 右下
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // 右上
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // 左上
			// 左侧面（x = -1）
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // 左下
			-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // 右下
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // 右上
			-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // 左上
			// 右侧面（x = 1）
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // 左下
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // 右下
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // 右上
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f  // 左上

		};

		unsigned int indices[] = {
			// 前面
			0, 1, 2,
			2, 3, 0,
			// 后面
			4, 5, 6,
			6, 7, 4,
			// 顶面
			8, 9, 10,
			10, 11, 8,
			// 底面
			12, 13, 14,
			14, 15, 12,
			// 左侧面
			16, 17, 18,
			18, 19, 16,
			// 右侧面
			20, 21, 22,
			22, 23, 20
		};

		// 创建网格并设置
		Mesh* mesh = new Mesh(positions, sizeof(positions) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
		SetMesh(mesh);
	}
}
