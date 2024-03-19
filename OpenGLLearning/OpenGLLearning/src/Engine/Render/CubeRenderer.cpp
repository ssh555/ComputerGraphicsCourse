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
		// ���¶��������԰������ߺ���������
		float positions[] = {
			// ����λ��            // ���㷨��          // ��������
			// ǰ�棨z = 0��
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // ����
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // ����
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // ����
			-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // ����
			// ���棨z = 1��
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // ����
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // ����
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // ����
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // ����
			// ���棨y = 1��
			-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // ����
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // ����
			 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // ����
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, // ����
			// ���棨y = -1��
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // ����
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // ����
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // ����
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // ����
			// ����棨x = -1��
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // ����
			-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // ����
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // ����
			-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // ����
			// �Ҳ��棨x = 1��
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // ����
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // ����
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // ����
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f  // ����

		};

		unsigned int indices[] = {
			// ǰ��
			0, 1, 2,
			2, 3, 0,
			// ����
			4, 5, 6,
			6, 7, 4,
			// ����
			8, 9, 10,
			10, 11, 8,
			// ����
			12, 13, 14,
			14, 15, 12,
			// �����
			16, 17, 18,
			18, 19, 16,
			// �Ҳ���
			20, 21, 22,
			22, 23, 20
		};

		// ������������
		Mesh* mesh = new Mesh(positions, sizeof(positions) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
		SetMesh(mesh);
	}
}
