#pragma once
#include "LineRenderer.h"


namespace Engine
{
	class CubeOutlineRenderer : public LineRenderer
	{
	public:
		CubeOutlineRenderer(GameObject* obj);
		void SetCubeOutlineMesh(); // 设置立方体轮廓线网格
	};


}

