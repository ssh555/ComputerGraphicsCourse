#include "Time.h"
#include <iostream>

namespace Engine
{
	void Time::Update()
	{
		auto currentTime = std::chrono::steady_clock::now();
		DeltaTime = std::chrono::duration<float>(currentTime - s_LastFrameTime).count();
		s_LastFrameTime = currentTime;
		std::cout << "Ö¡ÂÊÎª: " << (int)1.0f / DeltaTime << std::endl;
	}

	float Time::DeltaTime = 0.0f;
	std::chrono::steady_clock::time_point Time::s_LastFrameTime = std::chrono::steady_clock::now();
}