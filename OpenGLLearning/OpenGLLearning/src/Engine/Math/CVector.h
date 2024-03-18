#pragma once
#include <math.h>
#include <iostream>

namespace Engine
{
	using namespace std;
	class CEuler;
	class CQuaternion;

	class CVector
	{
	public:
		// ��̬��Ա�������������ϵĵ�λ����
		static CVector Up() {
			return CVector(0.0f, 1.0f, 0.0f);
		}

		// ��̬��Ա�������������µĵ�λ����
		static CVector Down() {
			return CVector(0.0f, -1.0f, 0.0f);
		}

		// ��̬��Ա��������������ĵ�λ����
		static CVector Left() {
			return CVector(-1.0f, 0.0f, 0.0f);
		}

		// ��̬��Ա�������������ҵĵ�λ����
		static CVector Right() {
			return CVector(1.0f, 0.0f, 0.0f);
		}

		// ��̬��Ա������������ǰ�ĵ�λ����
		static CVector Forward() {
			return CVector(0.0f, 0.0f, 1.0f);
		}

		// ��̬��Ա�������������ĵ�λ����
		static CVector Backward() {
			return CVector(0.0f, 0.0f, -1.0f);
		}

		static CVector Zero() {
			return CVector(0.0f, 0.0f, 0.0f);
		}

		static CVector One() {
			return CVector(1.0f, 1.0f, 1.0f);
		}


	public:
		//����������
		CVector();
		CVector(const float X, const float Y, const float Z);
		CVector(const CVector& vec);
		~CVector();

		//���ز�����
		CVector operator+(const CVector& vec);//���� + ������
		CVector operator-(const CVector& vec);
		CVector operator-(const CVector& vec) const;
		CVector operator-();
		CVector operator=(const CVector& vec);//���� = ������
		bool operator==(const CVector& vec);//���� == ������
		bool operator!=(const CVector& vec);//���� != ������

		friend CVector operator*(const float num, CVector& vec);//���� * ������ ��������
		CVector operator*(const float num);
		float operator*(const CVector& vec);
		CVector operator*(const CQuaternion& rot);
		CVector operator/(const CVector& vec);
		CVector& operator+=(const CVector& vec);

		//�������
		float dotMul(const CVector& vec);
		//�������
		CVector crossMul(const CVector& vec) const;
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
