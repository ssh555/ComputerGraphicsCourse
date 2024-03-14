#include "CQuaternion.h"
#include "CMatrix.h"
#include "CVector.h"
#include "CEuler.h"

namespace Engine
{

	CQuaternion CQuaternion::quatLookAt(const CVector& direction, const CVector& up)
	{
		CVector right = direction.crossMul(up).Normalized();

		CVector correctedUp = right.crossMul(direction).Normalized();

		// 构造一个旋转矩阵
		CMatrix rotationMatrix;
		rotationMatrix[0][0] = right.x;
		rotationMatrix[0][1] = right.y;
		rotationMatrix[0][2] = right.z;
		rotationMatrix[1][0] = correctedUp.x;
		rotationMatrix[1][1] = correctedUp.y;
		rotationMatrix[1][2] = correctedUp.z;
		rotationMatrix[2][0] = -direction.x;
		rotationMatrix[2][1] = -direction.y;
		rotationMatrix[2][2] = -direction.z;

		// 将旋转矩阵转换为四元数
		return rotationMatrix.ToCQuaternion();
	}






	CQuaternion::CQuaternion()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}
	CQuaternion::CQuaternion(const float X, const float Y, const float Z, const float W) {
		this->Set(X, Y, Z, W);
	}
	CQuaternion::CQuaternion(const CQuaternion& vec) {
		this->Set(vec.x, vec.y, vec.z, vec.w);
	}
	CQuaternion::CQuaternion(const float W, const CVector& vec) {
		this->Set(vec.x, vec.y, vec.z, W);
	}

	CQuaternion::~CQuaternion()
	{
	}

	void CQuaternion::Set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//四元数设置
	void CQuaternion::SetAngle(float angle, CVector axis) {
		this->w = cosf(angle / 180 * PI / 2);
		float SIN = sinf(angle / 180 * PI / 2);
		this->x = axis.x * SIN;
		this->y = axis.y * SIN;
		this->z = axis.z * SIN;
	}

	//重载赋值
	CQuaternion& CQuaternion::operator=(const CQuaternion& p) {
		this->Set(p.x, p.y, p.z, p.w);
		return *this;
	}

	//重载 +
	CQuaternion CQuaternion::operator+(const CQuaternion& p) {
		return CQuaternion(p.x + this->x, p.y + this->y, p.z + this->z, p.w + this->w);
	}

	//重载 -
	CQuaternion CQuaternion::operator-(const CQuaternion& p) {
		return CQuaternion(p.x - this->x, p.y - this->y, p.z - this->z, p.w - this->w);
	}

	//重载 ==
	bool CQuaternion::operator==(const CQuaternion& p) {
		if (fabsf(this->x - p.x) < 0.001f && fabsf(this->y - p.y) < 0.001f && fabsf(this->z - p.z) < 0.001f && fabsf(this->w - p.w) < 0.001f) {
			return true;
		}
		return false;
	}

	//重载数乘
	CQuaternion CQuaternion::operator*(float data) {
		return CQuaternion(data * this->x, data * this->y, data * this->z, data * this->w);
	}
	CQuaternion operator*(float data, CQuaternion& n) {
		return n * data;
	}

	//四元数乘法 叉乘
	CQuaternion CQuaternion::operator*(const CQuaternion& p) {
		float x1 = this->x;
		float x2 = p.x;
		float y1 = this->y;
		float y2 = p.y;
		float z1 = this->z;
		float z2 = p.z;
		float w1 = this->w;
		float w2 = p.w;
		float w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
		float x = w1 * x2 + x1 * w2 + z1 * y2 - y1 * z2;
		float y = w1 * y2 + y1 * w2 + x1 * z2 - z1 * x2;
		float z = w1 * z2 + z1 * w2 + y1 * x2 - x1 * y2;
		return CQuaternion(x, y, z, w);
	}

	//点乘
	float CQuaternion::dotMul(const CQuaternion& p) {
		CVector a(this->x, this->y, this->z);
		CVector b(p.x, p.y, p.z);
		return this->w * p.w + a.dotMul(b);
	}

	//求模
	float CQuaternion::len() {
		CVector a(this->x, this->y, this->z);
		return sqrtf(this->w * this->w + a.len() * a.len());
	}

	//标准化
	bool CQuaternion::Normalize() {
		float len = this->len();
		if (len == 0)
			return false;
		this->x /= len;
		this->y /= len;
		this->z /= len;
		this->w /= len;
		return true;
	}

	//返回共轭四元数
	CQuaternion CQuaternion::GetConjugate() {
		return CQuaternion(-this->x, -this->y, -this->z, this->w);
	}
	//求逆 改变自身
	CQuaternion& CQuaternion::Inverse() {
		CQuaternion conj = this->GetConjugate();
		float len2 = this->len();
		len2 *= len2;
		this->Set(conj.x / len2, conj.y / len2, conj.z / len2, conj.w / len2);
		return *this;
	}
	//求逆 不改变自身
	CQuaternion CQuaternion::GetInverse() {
		CQuaternion conj = this->GetConjugate();
		float len2 = this->len();
		len2 *= len2;
		return CQuaternion(conj.x / len2, conj.y / len2, conj.z / len2, conj.w / len2);
	}

	//求差
	CQuaternion CQuaternion::Div(const CQuaternion& b) {
		return this->GetInverse() * b;
	}

	//求旋转角和角度
	void CQuaternion::GetAngle(float& angle, CVector& axis) {
		CQuaternion t = *this;
		t.Normalize();
		angle = acosf(t.w) * 2;
		float SIN = sinf(angle / 2);
		angle = angle / PI * 180;
		axis[0] = t.x / SIN;
		axis[1] = t.y / SIN;
		axis[2] = t.z / SIN;
	}

	//幂
	CQuaternion CQuaternion::operator^(float t) {
		float a = acosf(this->w);
		float SIN = sinf(a);
		if (fabsf(SIN) < 0.00001f) {
			CVector n(0, 0, 0);
			return CQuaternion(cosf(t * a), n);
		}
		else {
			CVector n(this->x / SIN, this->y / SIN, this->z / SIN);
			n = n * sinf(t * a);
			return CQuaternion(cosf(t * a), n);
		}
	}

	//插值。从当前四元数插值到Vend四元数,t是参数[0,1]
	CQuaternion CQuaternion::Slerp(const CQuaternion& vend, float t) {
		CQuaternion q0 = *this;
		q0.Normalize();
		CQuaternion q1 = vend;
		q1.Normalize();
		q0 = ((q1 * q0.GetInverse()) ^ t) * q0;
		//cout << q0.x << " " << q0.y << " " << q0.z << " " << q0.w << endl;
		return q0;
		//return q0 * ((q0.Div(q1))^t);
	}
	//插值。一次插值出n个数据。插值参数保存在数组t中，结果返回到数组Result中。
	void CQuaternion::Slerp(const CQuaternion& vend, int n, float* t, CQuaternion* Result) {
		for (int i = 0; i < n; ++i) {
			Result[i] = this->Slerp(vend, t[i]);
		}
	}

	//四元数转欧拉角
	CEuler CQuaternion::ToCEuler() {
		float x = this->x;
		float y = this->y;
		float z = this->z;
		float w = this->w;
		//printf("%f %f %f %f\n", x, y, z, w);
		float t = (2 * (w * x - y * z));

		float p = asinf(t);
		if (fabsf(cosf(p)) > 0.001f) {
			float h = atan2f(2 * (w * y + x * z), (1 - 2 * (x * x + y * y))) / PI * 180;
			float b = atan2f(2 * (w * z + y * x), (1 - 2 * (z * z + x * x))) / PI * 180;
			//printf("%f %f %f\n", h, p, b);
			//cout << p / PI * 180 << endl;
			return CEuler(h, p / PI * 180, b);
		}
		else {
			float h = atan2f(2 * (w * y - x * z), (1 - 2 * (z * z + y * y))) / PI * 180;
			float b = 0;
			//printf("%f %f %f\n", h, p, b);
			//cout << p / PI * 180 << endl;
			return CEuler(h, p / PI * 180, b);
		}


	}

	//四元数转矩阵
	CMatrix CQuaternion::ToCMatrix() {
		float x = this->x;
		float y = this->y;
		float z = this->z;
		float w = this->w;
		float p[16];
		p[0 * 4 + 0] = 1 - 2 * y * y - 2 * z * z;
		p[0 * 4 + 1] = 2 * x * y + 2 * w * z;
		p[0 * 4 + 2] = 2 * x * z - 2 * w * y;
		p[0 * 4 + 3] = 0;
		p[1 * 4 + 0] = 2 * x * y - 2 * w * z;
		p[1 * 4 + 1] = 1 - 2 * x * x - 2 * z * z;
		p[1 * 4 + 2] = 2 * y * z + 2 * w * x;
		p[1 * 4 + 3] = 0;
		p[2 * 4 + 0] = 2 * x * z + 2 * w * y;
		p[2 * 4 + 1] = 2 * y * z - 2 * w * x;
		p[2 * 4 + 2] = 1 - 2 * x * x - 2 * y * y;
		p[2 * 4 + 3] = 0;
		p[3 * 4 + 0] = 0;
		p[3 * 4 + 1] = 0;
		p[3 * 4 + 2] = 0;
		p[3 * 4 + 3] = 1;
		return CMatrix(p);
	}

}
