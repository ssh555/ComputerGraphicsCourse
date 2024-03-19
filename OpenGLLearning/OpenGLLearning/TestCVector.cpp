#include "TestCVector.h"
#include <iostream>
#include "Engine/Math/CVector.h"
#include <fstream>
#include <iomanip>


TestCVector::TestCVector()
{
	cal();
}

void TestCVector::outVec(CVector& vec)
{
	std::cout << vec.x << " " << vec.y << " " << vec.z << endl;
}

const std::vector<std::string> TestCVector::split(const std::string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

void TestCVector::cal()
{
	//打开 in.txt 文件，等待读取
	ifstream fin("res/CVector/test.txt");
	//打开 out.txt 文件，等待写入
	ofstream fout("out.txt");

	if (!fin.is_open()) {
		cout << "输入文件打开失败" << endl;
		return;
	}
	if (!fout.is_open()) {
		cout << "输出文件打开失败" << endl;
		return;
	}

	//操作文件输入输出
	string str;
	float x, y, z;
	while (!fin.eof())
	{
		fin >> str;
		if (str == "向量相加") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//第二个向量
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1 + vec2;
			fout << "向量相加" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.z << endl;
		}

		else if (str == "向量点乘") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//第二个向量
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			fout << "向量点乘" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.dotMul(vec2) << endl;
		}


		else if (str == "向量叉乘") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//第二个向量
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1.crossMul(vec2);
			fout << "向量叉乘" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.z << endl;
		}

		else if (str == "向量标准化") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			CVector vec = vec1.Normalized();
			fout << "向量标准化" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.z << endl;
		}

		else if (str == "向量求模") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			fout << "向量求模" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.len() << endl;
		}

		else if (str == "向量投影") {
			//第一个向量
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//第二个向量
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1.project(vec2);
			fout << "向量投影" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec2.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.z << endl;
		}
		//cout << str << endl;
	}



	//打开的文件，最终需要手动关闭
	fin.close();
	fout.close();
}
