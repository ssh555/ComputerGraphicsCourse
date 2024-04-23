#include "CQuaternion.h"
#include "CMatrix.h"
#include "CVector.h"
#include "CEuler.h"

namespace Engine
{

	//CQuaternion CQuaternion::quatLookAt(const CVector& direction, const CVector& up)
	//{
	//	CVector right = direction.crossMul(up).Normalized();

	//	CVector correctedUp = right.crossMul(direction).Normalized();

	//	// 构造一个旋转矩阵
	//	CMatrix rotationMatrix;
	//	rotationMatrix[0][0] = right.x;
	//	rotationMatrix[0][1] = right.y;
	//	rotationMatrix[0][2] = right.z;
	//	rotationMatrix[1][0] = correctedUp.x;
	//	rotationMatrix[1][1] = correctedUp.y;
	//	rotationMatrix[1][2] = correctedUp.z;
	//	rotationMatrix[2][0] = -direction.x;
	//	rotationMatrix[2][1] = -direction.y;
	//	rotationMatrix[2][2] = -direction.z;

	//	// 将旋转矩阵转换为四元数
	//	return rotationMatrix.ToCQuaternion();
	//}
	CQuaternion CQuaternion::quatLookAt(const CVector& direction, const CVector& up)
	{
		// 计算右方向向量
		CVector right = up.crossMul(direction).Normalized();
		
		// 计算修正后的上方向向量
		CVector correctedUp = direction.crossMul(right).Normalized();

		// 构造一个旋转矩阵
		CMatrix rotationMatrix;
		rotationMatrix[0][0] = right.x;
		rotationMatrix[0][1] = right.y;
		rotationMatrix[0][2] = right.z;
		rotationMatrix[1][0] = correctedUp.x;
		rotationMatrix[1][1] = correctedUp.y;
		rotationMatrix[1][2] = correctedUp.z;
		rotationMatrix[2][0] = direction.x;
		rotationMatrix[2][1] = direction.y;
		rotationMatrix[2][2] = direction.z;

		// 将旋转矩阵转换为四元数
		CQuaternion qua = rotationMatrix.ToCQuaternion();
		qua.Normalize();
		return qua;
	}
	CQuaternion CQuaternion::quatFromAxisAngle(const CVector& axis, float angle)
	{
		if (angle > PI)
		{
			angle -= PI * 2;
		}
		if (angle < -PI)
		{
			angle += PI * 2;
		}
		// 计算旋转角的一半
		//float halfAngle = CMath::radians(angle) * 0.5f;
		float halfAngle = angle * 0.5f;

		// 计算旋转轴的单位向量
		CVector normalizedAxis = axis.Normalized();

		// 计算旋转轴的旋转四元数部分
		float sinHalfAngle = sin(halfAngle);
		float cosHalfAngle = cos(halfAngle);

		// 创建旋转四元数
		CQuaternion result;
		result.x = normalizedAxis.x * sinHalfAngle;
		result.y = normalizedAxis.y * sinHalfAngle;
		result.z = normalizedAxis.z * sinHalfAngle;
		result.w = cosHalfAngle;

		return result;
	}

	Engine::CQuaternion CQuaternion::quatFromMatrix(const CMatrix& matrix)
	{
		float trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
		float s;
		CQuaternion quat;

		if (trace > 0.0f) {
			s = 0.5f / sqrt(trace + 1.0f);
			quat.w = 0.25f / s;
			quat.x = (matrix[2][1] - matrix[1][2]) * s;
			quat.y = (matrix[0][2] - matrix[2][0]) * s;
			quat.z = (matrix[1][0] - matrix[0][1]) * s;
		}
		else {
			if (matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2]) {
				s = 2.0f * sqrt(1.0f + matrix[0][0] - matrix[1][1] - matrix[2][2]);
				quat.w = (matrix[2][1] - matrix[1][2]) / s;
				quat.x = 0.25f * s;
				quat.y = (matrix[0][1] + matrix[1][0]) / s;
				quat.z = (matrix[0][2] + matrix[2][0]) / s;
			}
			else if (matrix[1][1] > matrix[2][2]) {
				s = 2.0f * sqrt(1.0f + matrix[1][1] - matrix[0][0] - matrix[2][2]);
				quat.w = (matrix[0][2] - matrix[2][0]) / s;
				quat.x = (matrix[0][1] + matrix[1][0]) / s;
				quat.y = 0.25f * s;
				quat.z = (matrix[1][2] + matrix[2][1]) / s;
			}
			else {
				s = 2.0f * sqrt(1.0f + matrix[2][2] - matrix[0][0] - matrix[1][1]);
				quat.w = (matrix[1][0] - matrix[0][1]) / s;
				quat.x = (matrix[0][2] + matrix[2][0]) / s;
				quat.y = (matrix[1][2] + matrix[2][1]) / s;
				quat.z = 0.25f * s;
			}
		}

		return quat;
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
		if (this->w * p.x >= 0)
		{
			if (fabsf(this->x - p.x) < 0.001f && fabsf(this->y - p.y) < 0.001f && fabsf(this->z - p.z) < 0.001f && fabsf(this->w - p.w) < 0.001f) {
				return true;
			}
		}
		else
		{
			if (fabsf(this->x + p.x) < 0.001f && fabsf(this->y + p.y) < 0.001f && fabsf(this->z + p.z) < 0.001f && fabsf(this->w + p.w) < 0.001f) {
				return true;
			}
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
		float x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
		float y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
		float z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;
		return CQuaternion(x, y, z, w);
	}

	CVector CQuaternion::operator*(const CVector& vec)
	{
		// 将四元数视为旋转矩阵，并将向量视为列向量
		// 计算四元数的逆
		CQuaternion invQuat = GetConjugate();

		// 将向量转换为四元数（x, y, z, 0），这样可以与旋转矩阵相乘
		CQuaternion vecQuat(0.0f, vec);

		// 计算结果四元数
		CQuaternion resultQuat = (*this * vecQuat) * invQuat;

		// 返回结果向量（取四元数的前三个分量）
		return CVector(resultQuat.x, resultQuat.y, resultQuat.z);
	}

	Engine::CVector CQuaternion::operator*(const CVector& vec) const
	{
		// 将四元数转换为四元数对象（假设存在名为 Quaternion 的类）
		CQuaternion q(x, y, z, w);
		// 计算四元数的共轭
		CQuaternion qConjugate = q.GetConjugate();

		// 创建一个四元数表示向量
		CQuaternion v(vec.x, vec.y, vec.z, 0);

		// 应用四元数的旋转作用于向量
		CQuaternion rotatedVector = (q * v) * qConjugate;

		// 返回旋转后的向量
		return CVector(rotatedVector.x, rotatedVector.y, rotatedVector.z);
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
	CQuaternion CQuaternion::Div(CQuaternion& b) {
		return b * this->GetInverse();
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
		if (angle > 180)
		{
			angle -= 180 * 2;
		}
		if (angle < -180)
		{
			angle += 180 * 2;
		}
	}

	//幂
	CQuaternion CQuaternion::operator^(float t) {
		// 计算四元数的模长
		float length = sqrt(x * x + y * y + z * z + w * w);
		// 计算幅角
		float angle = acos(w / length);
		// 计算幅角的三角函数
		float sinAngle = sin(angle);

		// 计算新的幅角和新的向量部分
		float newAngle = angle * t;
		float newSinAngle = sin(newAngle);
		float scaleFactor = newSinAngle / sinAngle;

		// 新的向量部分
		CVector newVector(x * scaleFactor, y * scaleFactor, z * scaleFactor);

		// 新的标量部分
		float newW = cos(newAngle) * length;

		return CQuaternion(newW, newVector);
	}


	//插值。从当前四元数插值到Vend四元数, t 是参数[0,1]
	CQuaternion CQuaternion::Slerp(const CQuaternion& vend, float t) {
		// 获取起始四元数和目标四元数
		CQuaternion q0 = *this;
		CQuaternion q1 = vend;

		// 归一化四元数
		q0.Normalize();
		q1.Normalize();

		//// 计算两个四元数之间的夹角
		//float dotProduct = q0.dotMul(q1);
		//float theta = acos(dotProduct);

		//// 计算插值参数
		//float sinTheta = sin(theta);
		//float coef1 = sin((1 - t) * theta) / sinTheta;
		//float coef2 = sin(t * theta) / sinTheta;

		//// 执行插值
		//CQuaternion result = q0 * coef1 + q1 * coef2;

		//CQuaternion result = ((q1 * q0.GetInverse()) ^ t) * q0;
		CQuaternion result = q1 * q0.GetInverse();
		CVector axis;
		float angle;
		result.GetAngle(angle, axis);
		result.SetAngle(angle * t, axis);
		//result = CQuaternion::quatFromAxisAngle(axis, angle * t / 180 * PI);
		result = result * q0;
		result.Normalize();
		return result;
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
			//h = std::_Is_nan(h) ? 180 : h;
			float b = atan2f(2 * (w * z + y * x), (1 - 2 * (z * z + x * x))) / PI * 180;
			z = std::_Is_nan(z) ? 90 : z;
			//printf("%f %f %f\n", h, p, b);
			//cout << p / PI * 180 << endl;
			p = std::_Is_nan(p) ? 90 / 180 * PI : p;
			return CEuler(h, p / PI * 180, b);
		}
		else {
			float h = atan2f(2 * (w * y - x * z), (1 - 2 * (z * z + y * y))) / PI * 180;
			//h = std::_Is_nan(h) ? 180 : h;
			float b = 0;
			//printf("%f %f %f\n", h, p, b);
			//cout << p / PI * 180 << endl;
			p = std::_Is_nan(p) ? 90 / 180 * PI : p;
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

	Engine::CVector CQuaternion::GetVectorPart()
	{
		return CVector(this->x, this->y, this->z);
	}

}
