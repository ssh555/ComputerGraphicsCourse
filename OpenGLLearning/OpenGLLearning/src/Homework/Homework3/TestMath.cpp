#include "TestMath.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Engine/Math/CEuler.h"
#include "Engine/Math/CVector.h"
#include "Engine/Math/CQuaternion.h"
#include "Engine/Math/CMatrix.h"


Engine::TestMath::TestMath()
{
	cal();
}

const std::vector<std::string> Engine::TestMath::split(const std::string& s, const char& c)
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

void Engine::TestMath::cal()
{
	//打开 in.txt 文件，等待读取
	ifstream fin("res/CMath/test.txt");
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
	float x, y, z, w;
	while (!fin.eof())
	{
		fin >> str;
		if (str == "欧拉角转换向量") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CEuler euler(x, y, z);
			//euler.Normal();
			CVector* updir = new CVector();
			CVector vec = euler.ToCVector(updir);
			fout << "欧拉角转换向量" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << "\t"
				<< setiosflags(ios::fixed) << setprecision(6) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vec.z << endl;
				//<< setiosflags(ios::fixed) << setprecision(6) << updir->x << ","
				//<< setiosflags(ios::fixed) << setprecision(6) << updir->y << ","
				//<< setiosflags(ios::fixed) << setprecision(6) << updir->z << endl;
			delete updir;
		}
		else if (str == "向量转换欧拉角") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec(x, y, z);
			CEuler euler = vec.ToCEuler();
			//euler.Normal();
			fout << "向量转换欧拉角" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vec.z << "\t"
				<< setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << endl;
		}
		else if (str == "欧拉角转换四元数") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CEuler euler(x, y, z);
			CQuaternion q = euler.ToQuaternion();
			fout << "欧拉角转换四元数" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << "\t"
				<< setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << endl;
		}
		else if (str == "四元数转换欧拉角") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q(x, y, z, w);
			CEuler euler = q.ToCEuler();
			//euler.Normal();
			fout << "四元数转换欧拉角" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << "\t"
				<< setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << endl;
		}
		else if (str == "矩阵转换欧拉角") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix(p);
			CEuler euler = matrix.ToCEuler();
			//euler.Normal();
			fout << "矩阵转换欧拉角" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << matrix[3][3] << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << endl;

		}
		else if (str == "欧拉角转换矩阵") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CEuler euler(x, y, z);
			//euler.Normal();
			CMatrix matrix = euler.ToCMatrix();
			fout << "欧拉角转换矩阵" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << matrix[3][3] << endl;
		}
		else if (str == "矩阵转换四元数") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix(p);
			CQuaternion q = matrix.ToCQuaternion();
			fout << "矩阵转换四元数" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << matrix[3][3] << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << endl;
		}
		else if (str == "四元数转换矩阵") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q(x, y, z, w);
			CMatrix matrix = q.ToCMatrix();
			fout << "四元数转换矩阵" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << matrix[3][3] << endl;
		}
		else if (str == "欧拉角标准化") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CEuler euler(x, y, z);

			fout << "欧拉角标准化" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << "\t";
			euler.Normal();
			fout << setiosflags(ios::fixed) << setprecision(6) << euler.h << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.p << ","
				<< setiosflags(ios::fixed) << setprecision(6) << euler.b << endl;

		}
		else if (str == "四元数单位化") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q(x, y, z, w);

			fout << "四元数单位化" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << "\t";
			q.Normalize();
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << endl;;

		}
		else if (str == "四元数相乘") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q1(x, y, z, w);
			fin >> str;
			res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q2(x, y, z, w);

			CQuaternion q = q2 * q1;

			fout << "四元数相乘" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q1.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q2.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << endl;;
		}
		else if (str == "四元数求差") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q1(x, y, z, w);
			fin >> str;
			res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q2(x, y, z, w);

			CQuaternion q = q1.Div(q2);

			fout << "四元数求差" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q1.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q2.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << endl;;
		}
		else if (str == "四元数点乘") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q1(x, y, z, w);
			fin >> str;
			res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q2(x, y, z, w);

			float dres = q1.dotMul(q2);

			fout << "四元数点乘" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q1.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q2.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << dres << endl;;
		}
		else if (str == "四元数求逆") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q1(x, y, z, w);
			CQuaternion q2 = q1.GetInverse();

			fout << "四元数求逆" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q1.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q1.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << q2.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q2.z << endl;
		}
		else if (str == "四元数求角度和旋转轴") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q(x, y, z, w);
			float angle;
			CVector axis;
			q.GetAngle(angle, axis);

			fout << "四元数求角度和旋转轴" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << angle << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << axis.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << axis.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << axis.z << endl;

		}
		else if (str == "四元数插值") {
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion q(x, y, z, w);
			fin >> str;
			res = split(str, ',');
			w = stringToNum<float>(res[0]);
			x = stringToNum<float>(res[1]);
			y = stringToNum<float>(res[2]);
			z = stringToNum<float>(res[3]);
			CQuaternion vend(x, y, z, w);
			fin >> str;
			res = split(str, ',');
			float t = stringToNum<float>(res[0]);
			CQuaternion qres = q.Slerp(vend, t);


			fout << "四元数插值" << endl;
			fout << setiosflags(ios::fixed) << setprecision(6) << q.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << q.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << vend.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vend.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vend.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << vend.z << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << t << "\t";
			fout << setiosflags(ios::fixed) << setprecision(6) << qres.w << ","
				<< setiosflags(ios::fixed) << setprecision(6) << qres.x << ","
				<< setiosflags(ios::fixed) << setprecision(6) << qres.y << ","
				<< setiosflags(ios::fixed) << setprecision(6) << qres.z << endl;
		}
		else if (str == "矩阵正交化")
		{
			//矩阵
			fin >> str;
			vector<string> res = split(str, ',');
			for (int i = 0; i < 16; ++i)
				p[i] = stringToNum<float>(res[i]);
			CMatrix matrix(p);
			CMatrix m = CMatrix::Orthogonalize(matrix);
			fout << "矩阵正交化" << endl;
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << matrix[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << matrix[3][3] << "\t";
			for (int i = 0; i < 15; ++i) {
				fout << setiosflags(ios::fixed) << setprecision(6) << m[i / 4][i % 4] << ",";
			}
			fout << setiosflags(ios::fixed) << setprecision(6) << m[3][3] << endl;
		}
	}
}
