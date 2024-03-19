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
	//�� in.txt �ļ����ȴ���ȡ
	ifstream fin("res/CVector/test.txt");
	//�� out.txt �ļ����ȴ�д��
	ofstream fout("out.txt");

	if (!fin.is_open()) {
		cout << "�����ļ���ʧ��" << endl;
		return;
	}
	if (!fout.is_open()) {
		cout << "����ļ���ʧ��" << endl;
		return;
	}

	//�����ļ��������
	string str;
	float x, y, z;
	while (!fin.eof())
	{
		fin >> str;
		if (str == "�������") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//�ڶ�������
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1 + vec2;
			fout << "�������" << endl;
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

		else if (str == "�������") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//�ڶ�������
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			fout << "�������" << endl;
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


		else if (str == "�������") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//�ڶ�������
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1.crossMul(vec2);
			fout << "�������" << endl;
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

		else if (str == "������׼��") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			CVector vec = vec1.Normalized();
			fout << "������׼��" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec.z << endl;
		}

		else if (str == "������ģ") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			fout << "������ģ" << endl;
			fout << setiosflags(ios::fixed) << setprecision(2) << vec1.x << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.y << ","
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.z
				<< "\t"
				<< setiosflags(ios::fixed) << setprecision(2) << vec1.len() << endl;
		}

		else if (str == "����ͶӰ") {
			//��һ������
			fin >> str;
			vector<string> res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec1(x, y, z);

			//�ڶ�������
			fin >> str;
			res = split(str, ',');
			x = stringToNum<float>(res[0]);
			y = stringToNum<float>(res[1]);
			z = stringToNum<float>(res[2]);
			CVector vec2(x, y, z);

			CVector vec = vec1.project(vec2);
			fout << "����ͶӰ" << endl;
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



	//�򿪵��ļ���������Ҫ�ֶ��ر�
	fin.close();
	fout.close();
}
