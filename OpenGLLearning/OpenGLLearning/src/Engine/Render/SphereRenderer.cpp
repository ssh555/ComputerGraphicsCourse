#include "SphereRenderer.h"
#include "../Math/CMath.h"
#include "Mesh.h"

Engine::SphereRenderer::SphereRenderer(GameObject* obj, float radius /*= 1.0f*/, unsigned int rings /*= 20*/, unsigned int sectors /*= 20*/) : MeshRenderer(obj)
{
	SetSphereMesh(radius, rings, sectors);
}

void Engine::SphereRenderer::SetSphereMesh(float radius, unsigned int rings, unsigned int sectors)
{
	std::vector<float> positions;
	std::vector<unsigned int> indices;

	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);

	for (unsigned int r = 0; r < rings; ++r) {
		for (unsigned int s = 0; s < sectors; ++s) {
			float const y = sin(-CMath::PI * 0.5f + CMath::PI * r * R);
			float const x = cos(2 * CMath::PI * s * S) * sin(CMath::PI * r * R);
			float const z = sin(2 * CMath::PI * s * S) * sin(CMath::PI * r * R);

			positions.push_back(x * radius);
			positions.push_back(y * radius);
			positions.push_back(z * radius);
		}
	}

	for (unsigned int r = 0; r < rings - 1; ++r) {
		for (unsigned int s = 0; s < sectors - 1; ++s) {
			indices.push_back(r * sectors + s);
			indices.push_back((r + 1) * sectors + (s + 1));
			indices.push_back(r * sectors + (s + 1));

			indices.push_back(r * sectors + s);
			indices.push_back((r + 1) * sectors + s);
			indices.push_back((r + 1) * sectors + (s + 1));
		}
	}

	Mesh mesh(positions.data(), static_cast<unsigned int>(positions.size() / 3),
		indices.data(), static_cast<unsigned int>(indices.size()));
	SetMesh(&mesh);
}
