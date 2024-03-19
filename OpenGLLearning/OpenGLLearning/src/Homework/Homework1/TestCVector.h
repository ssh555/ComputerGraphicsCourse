#pragma once
#include <vector>
#include <string>
#include <sstream>


namespace Engine
{
	class CVector;
}
using namespace Engine;

class TestCVector
{
public:
	TestCVector();
	void outVec(CVector& vec);
	const std::vector<std::string> split(const std::string& s, const char& c);
	//×Ö·û´®×ªÊý×Ö
	template <class Type>
	Type stringToNum(const std::string& str);
	void cal();
};

template <class Type>
Type TestCVector::stringToNum(const std::string& str)
{
	std::istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

