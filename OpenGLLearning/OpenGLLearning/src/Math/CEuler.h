#pragma once

namespace Math
{
	class CVector;
	class CMatrix;
	class CQuaternion;
#define PI 3.1415926f

	class CEuler
	{
	public:
		CEuler();
		CEuler(const float X, const float Y, const float Z);
		CEuler(const CEuler& vec);
		~CEuler();
		//ƫ������������ת
		float h, p, b;
		//���ýǵ�ֵ
		void Set(float h, float p, float b);

		//ŷ����ת��Ϊ����
		//�������updirָ�벻Ϊ0�����������ͬʱ����Ϸ�������updir��
		CVector ToCVector(CVector* updir = 0);

		//ŷ����ת����
		CMatrix ToCMatrix();

		//ŷ����ת��Ԫ��
		CQuaternion ToQuaternion();

		//ŷ���ǹ淶��
		void Normal();

		operator float* () { return &h; }


	private:

	};

}
