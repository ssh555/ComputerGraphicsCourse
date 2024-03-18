#pragma once

#include <chrono>

namespace Engine
{
	class Time
	{
	public:
		static void Update();


		static float DeltaTime;

	private:
		static std::chrono::steady_clock::time_point s_LastFrameTime;
	};


}
