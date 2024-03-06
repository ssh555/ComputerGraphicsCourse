#pragma once

namespace Math
{
	class CVector;
	class CEuler;
	class CMatrix;

	class CQuaternion
	{
	public:
		CQuaternion();
		CQuaternion(const float X, const float Y, const float Z, const float W);
		CQuaternion(const float W, const CVector& vec);
		CQuaternion(const CQuaternion& vec);
		~CQuaternion();

		float x, y, z, w;
		void Set(float x, float y, float z, float w);

		//��Ԫ������
		void SetAngle(float angle, CVector axis);
		//���ظ�ֵ
		CQuaternion& operator=(const CQuaternion& p);
		//���� +
		CQuaternion operator+(const CQuaternion& p);
		//���� -
		CQuaternion operator-(const CQuaternion& p);
		//���� ==
		bool operator==(const CQuaternion& p);
		//��������
		CQuaternion operator*(float data);
		friend CQuaternion operator*(float data, CQuaternion& n);
		//��
		CQuaternion operator^(float t);
		//��Ԫ���˷� ���
		CQuaternion operator*(const CQuaternion& p);
		//���
		float dotMul(const CQuaternion& p);
		//��ģ
		float len();
		//��׼��
		bool Normalize();
		//���ع�����Ԫ��
		CQuaternion GetConjugate();
		//���� �ı�����
		CQuaternion& Inverse();
		//���� ���ı�����
		CQuaternion GetInverse();
		//���
		CQuaternion Div(const CQuaternion& b);
		//����ת�ǺͽǶ�
		void GetAngle(float& angle, CVector& axis);
		//��ֵ���ӵ�ǰ��Ԫ����ֵ��Vend��Ԫ��,t�ǲ���[0,1]
		CQuaternion Slerp(const CQuaternion& vend, float t);
		//��ֵ��һ�β�ֵ��n�����ݡ���ֵ��������������t�У�������ص�����Result�С�
		void Slerp(const CQuaternion& vend, int n, float* t, CQuaternion* Result);

		//��Ԫ��תŷ����
		CEuler ToCEuler();
		//��Ԫ��ת����
		CMatrix ToCMatrix();

		operator float* () { return &x; };

	private:

	};

}
