#include "CapsuleRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "../Math/CMath.h"

namespace Engine
{

	CapsuleRenderer::CapsuleRenderer(GameObject* obj, float radius /*= 1.0f*/, float height /*= 2.0f*/, unsigned int rings /*= 20*/, unsigned int sectors /*= 20*/)
		: MeshRenderer(obj)
	{
		SetCapsuleMesh(radius, height, rings, sectors);
		m_mat = new Material();

		m_mat->SetUniform1f("ambientStrength", 0.6f);
		m_mat->SetUniform1f("specularStrength", 0.5f);
		m_mat->SetUniform1f("shininess", 1);
	}

	void Engine::CapsuleRenderer::SetCapsuleMesh(float radius, float height, unsigned int rings, unsigned int sectors)
	{
		std::vector<float> positions;
		std::vector<unsigned int> indices;

		// Generate the top hemisphere
		for (unsigned int r = 0; r <= rings / 2; ++r) {
			float const theta = CMath::PI * r / rings;
			float const y = cos(theta);
			float const y_offset = sin(theta);

			for (unsigned int s = 0; s < sectors; ++s) {
				float const phi = 2 * CMath::PI * s / sectors;
				float const x = cos(phi) * sin(theta);
				float const z = sin(phi) * sin(theta);

				// Vertex position
				positions.push_back(x * radius);
				positions.push_back(y * radius + height / 2); // Translate upwards
				positions.push_back(z * radius);

				// Normal
				positions.push_back(x);
				positions.push_back(y);
				positions.push_back(z);

				// Texture coordinates
				positions.push_back(static_cast<float>(s) / (sectors - 1));
				positions.push_back(static_cast<float>(r) / rings);
			}
		}

		// Generate the bottom hemisphere
		for (unsigned int r = 0; r <= rings / 2; ++r) {
			float const theta = CMath::PI * r / rings + CMath::PI;
			float const y = cos(theta);
			float const y_offset = sin(theta);

			for (unsigned int s = 0; s < sectors; ++s) {
				float const phi = 2 * CMath::PI * s / sectors;
				float const x = cos(phi) * sin(theta);
				float const z = sin(phi) * sin(theta);

				// Vertex position
				positions.push_back(x * radius);
				positions.push_back(y * radius - height / 2); // Translate downwards
				positions.push_back(z * radius);

				// Normal
				positions.push_back(x);
				positions.push_back(y);
				positions.push_back(z);

				// Texture coordinates
				positions.push_back(static_cast<float>(s) / (sectors - 1));
				positions.push_back(static_cast<float>(r) / rings + 0.5f);
			}
		}

		// Generate the cylinder part
		for (unsigned int i = 0; i <= sectors; ++i) {
			float const phi = 2 * CMath::PI * i / sectors;
			float const x = cos(phi);
			float const z = sin(phi);

			// Top vertex
			positions.push_back(x * radius);
			positions.push_back(height / 2);
			positions.push_back(z * radius);

			// Normal
			positions.push_back(0);
			positions.push_back(1);
			positions.push_back(0);

			// Texture coordinates
			positions.push_back(static_cast<float>(i) / sectors);
			positions.push_back(0);

			// Bottom vertex
			positions.push_back(x * radius);
			positions.push_back(-height / 2);
			positions.push_back(z * radius);

			// Normal
			positions.push_back(0);
			positions.push_back(-1);
			positions.push_back(0);

			// Texture coordinates
			positions.push_back(static_cast<float>(i) / sectors);
			positions.push_back(1);
		}

		// Generate indices for the capsule
		for (unsigned int r = 0; r < rings / 2; ++r) {
			for (unsigned int s = 0; s < sectors - 1; ++s) {
				indices.push_back(r * sectors + s);
				indices.push_back((r + 1) * sectors + s);
				indices.push_back((r + 1) * sectors + (s + 1));

				indices.push_back(r * sectors + s);
				indices.push_back((r + 1) * sectors + (s + 1));
				indices.push_back(r * sectors + (s + 1));
			}
		}

		// Duplicate indices for the bottom hemisphere
		for (unsigned int r = rings / 2; r < rings; ++r) {
			for (unsigned int s = 0; s < sectors - 1; ++s) {
				indices.push_back(r * sectors + s);
				indices.push_back((r + 1) * sectors + (s + 1));
				indices.push_back((r + 1) * sectors + s);

				indices.push_back(r * sectors + s);
				indices.push_back(r * sectors + (s + 1));
				indices.push_back((r + 1) * sectors + (s + 1));
			}
		}

		// Indices for the cylinder part
		for (unsigned int i = 0; i < sectors; ++i) {
			// Upper face
			indices.push_back((rings + 1) * sectors + i * 2);
			indices.push_back((rings + 1) * sectors + i * 2 + 1);
			indices.push_back((rings + 1) * sectors + (i + 1) * 2);

			// Lower face
			indices.push_back((rings + 1) * sectors + i * 2 + 1);
			indices.push_back((rings + 1) * sectors + (i + 1) * 2 + 1);
			indices.push_back((rings + 1) * sectors + (i + 1) * 2);
		}

		// Create and set the mesh
		Mesh* mesh = new Mesh(positions.data(), static_cast<unsigned int>(positions.size()),
			indices.data(), static_cast<unsigned int>(indices.size()));
		SetMesh(mesh);
	}





}