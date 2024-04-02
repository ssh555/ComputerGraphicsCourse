#include "TestCMatrix.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Engine/Math/CMatrix.h"
#include "Engine/Math/CVector.h"
using namespace Engine;

TestCMatrix::TestCMatrix()
{
	cal();
}

const std::vector<std::string> TestCMatrix::split(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

void TestCMatrix::cal()
{
	//打开 in.txt 文件，等待读取
	ifstream fin("res/CMatrix/test.txt");
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
	float p[16];
	float x, y, z;
	while (!fin.eof())
	{
		fin >> str;
		if (str == "矩阵相乘") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix1(p);

			//矩阵
			fin >> str;
			res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix2(p);

			CMatrix matrix = matrix1 * matrix2;
			fout << "矩阵相乘" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[i/4][i%4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[3][3] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix2[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix2[3][3] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << endl;
		}

		else if (str == "矩阵乘向量") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix1(p);

			//矩阵
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);

			CVector vecR = matrix1.vecMul(vec);
			fout << "矩阵乘向量" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[3][3] << "\t";
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vec[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vec[2] << "\t";
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vecR[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vecR[2] << endl;
		}


		else if (str == "矩阵乘位置") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix1(p);

			//矩阵
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);

			CVector vecR = matrix1.posMul(vec);
			fout << "矩阵乘位置" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix1[3][3] << "\t";
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vec[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vec[2] << "\t";
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vecR[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vecR[2] << endl;
		}

		else if (str == "矩阵设置旋转") {
			//旋转角
			fin >> str;
			float seta = stringToNum<float>(str);

			//旋转轴
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);

			CMatrix matrix;
			matrix.SetRotate(seta, vec);
			fout << "矩阵设置旋转" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << seta << "\t";
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vec[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vec[2] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << endl;;

		}

		else if (str == "矩阵设置平移") {
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);

			CMatrix matrix;
			matrix.SetTrans(vec);
			fout << "矩阵设置平移" << endl;
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vec[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vec[2] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << endl;;
		}

		else if (str == "矩阵设置缩放") {
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);

			CMatrix matrix;
			matrix.SetScale(vec);
			fout << "矩阵设置缩放" << endl;
			for (int i = 0; i < 2; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << vec[i] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << vec[2] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << endl;
		}
		else if (str == "矩阵求逆") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix(p);
			fout << "矩阵求逆" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << "\t";
			matrix.Inverse();
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(2) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(2) << matrix[3][3] << endl;
		}
		//cout << str << endl;
	}



	//打开的文件，最终需要手动关闭
	fin.close();
	fout.close();
}
