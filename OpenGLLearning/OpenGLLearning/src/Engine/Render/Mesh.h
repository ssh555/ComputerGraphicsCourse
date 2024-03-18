#pragma once
#include <cstring>

namespace Engine
{
	class Mesh
	{
	public:
		Mesh(float* positions, unsigned int positionCount, unsigned int* indices, unsigned int indexCount)
			: m_positionCount(positionCount), m_indexCount(indexCount)
		{
			m_positions = new float[positionCount];
			std::memcpy(m_positions, positions, positionCount * sizeof(float));

			m_indices = new unsigned int[indexCount];
			std::memcpy(m_indices, indices, indexCount * sizeof(unsigned int));
		}

		~Mesh()
		{
			delete[] m_positions;
			delete[] m_indices;
		}

		const float* GetPositions() const { return m_positions; }
		const unsigned int* GetIndices() const { return m_indices; }
		unsigned int GetPositionCount() const { return m_positionCount; }
		unsigned int GetIndexCount() const { return m_indexCount; }

	private:
		float* m_positions;
		unsigned int m_positionCount;
		unsigned int* m_indices;
		unsigned int m_indexCount;
	};

}

