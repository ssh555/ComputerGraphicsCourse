#include "CVector.h"
#include "CEuler.h"
#include "CQuaternion.h"

namespace Engine
{
	//���캯��
//�޲ι���
	CVector::CVector() {
		this->x = y = z = 0;
	}
	//��ֵxyz����
	CVector::CVector(const float X, const float Y, const float Z) {
		this->SetVec(X, Y, Z);
	}
	//��������
	CVector::CVector(const CVector& vec) {
		this->SetVec(vec.x, vec.y, vec.z);
	}

	//��������
	CVector::~CVector() {

	}

	//����xyx����ֵ
	void CVector::SetVec(float X, float Y, float Z) {
		this->x = X;
		this->y = Y;
		this->z = Z;
	}

	//���ز�����
	CVector CVector::operator+(const CVector& vec) {
		return CVector(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	CVector CVector::operator-(const CVector& vec) {
		return CVector(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	CVector CVector::operator-(const CVector& vec) const {
		return CVector(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	CVector CVector::operator=(const CVector& vec) {
		this->SetVec(vec.x, vec.y, vec.z);
		return CVector(*this);
	}

	bool CVector::operator==(const CVector& vec) {
		if (fabs(this->x - vec.x) < 0.001f && fabs(this->y - vec.y) < 0.001f && fabs(this->z - vec.z) < 0.001f) {
			return true;
		}
		return false;
	}

	bool CVector::operator!=(const CVector& vec) {
		return !(*this == vec);
	}
	CVector CVector::operator*(const float num) {
		return CVector(this->x * num, this->y * num, this->z * num);
	}

	float CVector::operator*(const CVector& vec)
	{
		return this->dotMul(vec);
	}

	CVector CVector::operator*(const CQuaternion& rot)
	{
		return rot * (*this);
	}

	Engine::CVector CVector::operator*(const float num) const
	{
		return CVector(this->x * num, this->y * num, this->z * num);
	}

	Engine::CVector CVector::operator/(const CVector& vec)
	{
		// ���������Ӧ����������ĳ���
		float x = this->x / vec.x;
		float y = this->y / vec.y;
		float z = this->z / vec.z;

		return CVector(x, y, z);
	}

	Engine::CVector& CVector::operator+=(const CVector& vec)
	{
		// ��ÿ�������������
		x += vec.x;
		y += vec.y;
		z += vec.z;

		// ���ص�ǰ���������
		return *this;
	}

	CVector operator*(const float num, CVector& vec) {
		return CVector(vec.x * num, vec.y * num, vec.z * num);
	}

	//�������
	float CVector::dotMul(const CVector& vec) {
		return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
	}

	//�������
	CVector CVector::crossMul(const CVector& vec) const {
		return CVector(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
	}
	CVector CVector::crossMul(const CVector& vec) {
		return CVector(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
	}
	//������λ��
	void CVector::Normalize() {
		float len = this->len();
		this->SetVec(this->x / len, this->y / len, this->z / len);
	}
	CVector CVector::Normalized() {
		float len = this->len();
		return CVector(this->x / len, this->y / len, this->z / len);
	}

	//������ģ
	float CVector::len() {
		return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}

	//����ͶӰ
	CVector CVector::project(CVector& vec) {
		float length = this->dotMul(vec) / (vec.len());
		return CVector(vec.Normalized() * length);
	}

	//����������ת
	CVector CVector::RotateAxis(CVector& axis, float angle) {
		float Cos = cosf(angle);
		float Sin = sinf(angle);
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		float SumSquares = powf(x, 2) + powf(y, 2) + powf(z, 2);
		float SqrSumSquares = sqrtf(SumSquares);
		float R[3][3] = {
			(powf(x,2) + (powf(y,2) + powf(z,2)) * Cos) / (SumSquares), (x * y * (1 - Cos) / SumSquares - z * Sin / SqrSumSquares), (x * z * (1 - Cos) / SumSquares + y * Sin / SqrSumSquares),
			(y * x * (1 - Cos) / SumSquares + z * Sin / SqrSumSquares), (powf(y,2) + (powf(x,2) + powf(z,2)) * Cos) / (SumSquares), (z * y * (1 - Cos) / SumSquares - x * Sin / SqrSumSquares),
			(x * z * (1 - Cos) / SumSquares - y * Sin / SqrSumSquares), (y * z * (1 - Cos) / SumSquares + x * Sin / SqrSumSquares), (powf(z,2) + (powf(x,2) + powf(y,2)) * Cos) / (SumSquares)
		};
		CVector vec;
		for (int i = 0; i < 3; ++i) {
			vec[i] = R[i][0] * this->x + R[i][1] * this->y + R[i][2] * this->z;
		}
		return vec;
	}

	//����תΪŷ����
	CEuler CVector::ToCEuler() {
		CVector init(0, 0, -1);
		CVector nor = this->Normalized();
		if (fabs(x) > 0.001f) {
			float h = acos(init.dotMul(CVector(nor.x, 0, nor.z).Normalized())) / PI * (this->x > 0.001f ? -180 : 180);
			float p = acos(nor.dotMul(CVector(nor.x, 0, nor.z).Normalized())) / PI * (this->y > 0.001f ? 180 : -180);
			return CEuler(h, p, 0);
		}
		else {
			if (fabs(z) > 0.001f) {
				cout << acos(init.dotMul(CVector(0, nor.y, nor.z).Normalized())) << endl;
				float p = acos(init.dotMul(CVector(0, nor.y, nor.z).Normalized())) / PI * (this->y > 0.001f ? 180 : -180);
				return CEuler(0, p, 0);
			}
			else {
				if (fabs(y) < 0.001f)
					return CEuler(0, 0, 0);
				return CEuler(0, 90.0f * (y > 0.001f ? 1 : -1), 0);
			}
		}

	}
	CVector CVector::operator-() {
		return CVector(-this->x, -this->y, -this->z);
	}
}
