#include "CEuler.h"
#include "CVector.h"
#include "CQuaternion.h"
#include "CMatrix.h"

namespace Engine
{
	CEuler::CEuler()
	{
	}
	CEuler::CEuler(const float X, const float Y, const float Z) {
		this->Set(X, Y, Z);
	}
	CEuler::CEuler(const CEuler& vec) {
		this->Set(vec.h, vec.p, vec.b);
	}


	CEuler::~CEuler()
	{
	}

	//���ýǵ�ֵ
	void CEuler::Set(float h, float p, float b) {
		this->h = h;
		this->p = p;
		this->b = b;
	}

	//ŷ����ת��Ϊ����
	//�������updirָ�벻Ϊ0�����������ͬʱ����Ϸ�������updir��
	CVector CEuler::ToCVector(CVector* updir) {
		if (updir != 0) {
			CVector t(0, 1, 0);
			CMatrix matrix;
			matrix.SetRotate(this->h, CVector(0, 1, 0));
			t = matrix.vecMul(t);
			matrix.SetRotate(this->p, CVector(1, 0, 0));
			t = matrix.vecMul(t);
			matrix.SetRotate(this->b, CVector(0, 0, 1));
			t = matrix.vecMul(t);
			*updir = t;
		}
		CVector init(0, 0, -1);
		//cout << h << " " << p << " " << b << endl;
		CMatrix matrix;
		matrix.SetRotate(this->h, CVector(0, 1, 0));
		init = matrix.vecMul(init);
		//cout << init.x << " " << init.y << " " << init.z << endl;
		matrix.SetRotate(this->p, CVector(1, 0, 0));
		init = matrix.vecMul(init);
		//cout << init.x << " " << init.y << " " << init.z << endl;
		matrix.SetRotate(this->b, CVector(0, 0, 1));
		init = matrix.vecMul(init);
		//cout << init.x << " " << init.y << " " << init.z << endl;
		return init;
	}

	//ŷ����ת����
	CMatrix CEuler::ToCMatrix() {
		CMatrix mx, my, mz;
		mx.SetRotate(this->p, CVector(1, 0, 0));
		my.SetRotate(this->h, CVector(0, 1, 0));
		mz.SetRotate(this->b, CVector(0, 0, 1));
		return my * mx * mz;
	}

	//ŷ���ǹ淶��
	void CEuler::Normal() {
		float x = this->h;
		float y = this->p;
		float z = this->b;
		while ((x - 180) > 0.001f) {
			x -= 360;
		}
		while ((x + 180) < 0.001f)
		{
			x += 360;
		}
		while ((y - 90) > 0.001f) {
			y -= 180;
		}
		while ((y + 90) < 0.001f)
		{
			y += 180;
		}
		if (fabsf(y - 90) < 0.001f || fabs(y + 90) < 0.001f) {
			z = x;
		}
		else {
			while ((z - 180) > 0.001f) {
				z -= 360;
			}
			while ((z + 180) < 0.001f)
			{
				z += 360;
			}
		}
		this->Set(x, y, z);
	}

	//ŷ����ת��Ԫ��
	CQuaternion CEuler::ToQuaternion() {
		float cosY = cosf(this->h / 180 * PI / 2);
		float sinY = sinf(this->h / 180 * PI / 2);
		float cosX = cosf(this->p / 180 * PI / 2);
		float sinX = sinf(this->p / 180 * PI / 2);
		float cosZ = cosf(this->b / 180 * PI / 2);
		float sinZ = sinf(this->b / 180 * PI / 2);
		//cout << cosY << " " << sinY << " " << cosX << " " << sinX << " " << cosZ << " " << sinZ << endl;
		float w = cosX * cosY * cosZ + sinX * sinY * sinZ;
		float x = sinX * cosY * cosZ + cosX * sinY * sinZ;
		float y = cosX * sinY * cosZ - sinX * cosY * sinZ;
		float z = cosX * cosY * sinZ - sinX * sinY * cosZ;
		//printf("%f %f %f %f\n", x, y, z, w);
		return CQuaternion(x, y, z, w);
	}

}
