#pragma once
#include "LineRenderer.h"


namespace Engine
{
	class CubeOutlineRenderer : public LineRenderer
	{
	public:
		CubeOutlineRenderer(GameObject* obj);
		void SetCubeOutlineMesh(); // ��������������������
	};


}

