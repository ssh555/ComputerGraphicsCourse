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
		// ������Ķ�������
		float positions[] = {
			// ǰ���ĸ�����
			-0.5f, -0.5f,  0.5f, // ���� 0
			 0.5f, -0.5f,  0.5f, // ���� 1
			 0.5f,  0.5f,  0.5f, // ���� 2
			-0.5f,  0.5f,  0.5f, // ���� 3
			// �����ĸ�����
			 0.5f, -0.5f, -0.5f, // ���� 4
			-0.5f, -0.5f, -0.5f, // ���� 5
			-0.5f,  0.5f, -0.5f, // ���� 6
			 0.5f,  0.5f, -0.5f, // ���� 7
		};

		// �������������
		unsigned int indices[] = {
			// ǰ��
			0, 1, 1, 2, 2, 3, 3, 0,
			// ����
			4, 5, 5, 6, 6, 7, 7, 4,
			// ����ǰ�������
			0, 5, 1, 4, 2, 7, 3, 6,
		};

		// ������������
		Mesh* mesh = new Mesh(positions, sizeof(positions) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
		SetMesh(mesh);
	}


}