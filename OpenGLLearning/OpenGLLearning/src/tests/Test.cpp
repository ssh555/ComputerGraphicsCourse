#include "Test.h"
#include "imgui/imgui.h"
#include "Engine/Time/Time.h"

namespace test
{
	TestMenu::TestMenu(Test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{

	}

	void TestMenu::OnImGuiRender()
	{
		ImGui::Text("FPS: %d", (int)(1.0f / Engine::Time::DeltaTime));
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}

}


