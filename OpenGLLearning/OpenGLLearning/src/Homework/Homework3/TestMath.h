#pragma once
#include <vector>
#include <string>

namespace Engine
{
	class TestMath
	{
	public:
		TestMath();
		const std::vector<std::string> split(const std::string& s, const char& c);
		//×Ö·û´®×ªÊý×Ö
		template <class Type>
		Type stringToNum(const std::string& str);
		void cal();
	};
	template <class Type>
	Type TestMath::stringToNum(const std::string& str)
	{
		std::istringstream iss(str);
		Type num;
		iss >> num;
		return num;
	}
}

