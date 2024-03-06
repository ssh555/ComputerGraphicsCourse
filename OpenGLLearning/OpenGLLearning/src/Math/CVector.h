#pragma once
#include <math.h>
#include <iostream>

namespace Math
{
	using namespace std;
	class CEuler;

	class CVector
	{
	public:
		//����������
		CVector();
		CVector(const float X, const float Y, const float Z);
		CVector(const CVector& vec);
		~CVector();

		//���ز�����
		CVector operator+(const CVector& vec);//���� + ������
		CVector operator-(const CVector& vec);
		CVector operator-();
		CVector operator=(const CVector& vec);//���� = ������
		bool operator==(const CVector& vec);//���� == ������
		bool operator!=(const CVector& vec);//���� != ������

		friend CVector operator*(const float num, CVector& vec);//���� * ������ ��������
		CVector operator*(const float num);

		//�������
		float dotMul(const CVector& vec);
		//�������
		CVector crossMul(const CVector& vec);

		//������λ��
		//�ı�����
		void Normalize();
		//�����䣬���ص�λ����ֵ
		CVector Normalized();

		//������ģ
		float len();
		//����ͶӰ
		CVector project(CVector& vec);
		//������ת
		CVector RotateAxis(CVector& axis, float angle);

		//��������ֵ
		void SetVec(float X, float Y, float Z);

		//����תΪŷ����
		CEuler ToCEuler();

		operator float* () { return &x; }	//�Զ�����ת��

		//����(x,y,z)
		float x;
		float y;
		float z;
	};

}
