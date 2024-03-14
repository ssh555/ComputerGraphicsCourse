#include "CMatrix.h"
#include "CVector.h"
#include "CEuler.h"
#include "CQuaternion.h"

namespace Engine
{

	CMatrix CMatrix::ortho(float left, float right, float bottom, float top, float nearVal, float farVal)
	{
		CMatrix result;

		result[0][0] = 2.0f / (right - left);
		result[1][1] = 2.0f / (top - bottom);
		result[2][2] = -2.0f / (farVal - nearVal);
		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		result[3][2] = -(farVal + nearVal) / (farVal - nearVal);
		result[3][3] = 1.0f; // 设置为1
		return result;

	}

	CMatrix CMatrix::translate(const CMatrix& matrix, float x, float y, float z)
	{
		CMatrix result(matrix);

		result[3][0] += x;
		result[3][1] += y;
		result[3][2] += z;

		return result;
	}

	CMatrix CMatrix::translate(const CMatrix& matrix, const CVector& vec)
	{
		CMatrix result(matrix);

		result[3][0] += vec.x;
		result[3][1] += vec.y;
		result[3][2] += vec.z;

		return result;
	}

	CMatrix CMatrix::scale(const CMatrix& matrix, float scaleX, float scaleY, float scaleZ)
	{
		CMatrix result(matrix);
		result[0][0] *= scaleX;
		result[1][1] *= scaleY;
		result[2][2] *= scaleZ;
		return result;
	}

	CMatrix CMatrix::scale(const CMatrix& matrix, const CVector& vec)
	{
		CMatrix result(matrix);
		result[0][0] *= vec.x;
		result[1][1] *= vec.y;
		result[2][2] *= vec.z;
		return result;
	}

	CMatrix CMatrix::perspective(float fov, float aspectRatio, float nearVal, float farVal)
	{
		float tanHalfFov = std::tan(fov / 2.0f);
		float range = nearVal - farVal;

		CMatrix result;
		result[0][0] = 1.0f / (aspectRatio * tanHalfFov);
		result[0][1] = 0.0f;
		result[0][2] = 0.0f;
		result[0][3] = 0.0f;

		result[1][0] = 0.0f;
		result[1][1] = 1.0f / tanHalfFov;
		result[1][2] = 0.0f;
		result[1][3] = 0.0f;

		result[2][0] = 0.0f;
		result[2][1] = 0.0f;
		result[2][2] = (farVal + nearVal) / range;
		result[2][3] = -1.0f;

		result[3][0] = 0.0f;
		result[3][1] = 0.0f;
		result[3][2] = 2.0f * farVal * nearVal / range;
		result[3][3] = 0.0f;

		return result;
	}

	Engine::CMatrix CMatrix::lookAt(const CVector& eye, const CVector& center, const CVector& up)
	{
		// 计算摄像机的坐标系
		CVector forward = (center - eye).Normalized();
		CVector right = forward.crossMul(up).Normalized();
		CVector newUp = right.crossMul(forward).Normalized();

		// 构造视图矩阵
		CMatrix viewMatrix;
		viewMatrix[0][0] = right.x;
		viewMatrix[1][0] = right.y;
		viewMatrix[2][0] = right.z;
		viewMatrix[0][1] = newUp.x;
		viewMatrix[1][1] = newUp.y;
		viewMatrix[2][1] = newUp.z;
		viewMatrix[0][2] = -forward.x;
		viewMatrix[1][2] = -forward.y;
		viewMatrix[2][2] = -forward.z;
		viewMatrix[3][0] = -right.dotMul(eye);
		viewMatrix[3][1] = -newUp.dotMul(eye);
		viewMatrix[3][2] = forward.dotMul(eye);
		viewMatrix[3][3] = 1.0f;

		return viewMatrix;
	}





	CMatrix::CMatrix()
	{
		std::memset(data, 0, sizeof(data));
	}

	CMatrix::CMatrix(float value)
	{
		// 设置对角线上的值为指定值，其他为0
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				data[i][j] = (i == j) ? value : 0.0f;
			}
		}
	}

	CMatrix::~CMatrix()
	{
	}

	CMatrix::CMatrix(float* p) {
		this->SetMatrix(p);
	}
	CMatrix::CMatrix(const CMatrix& p) {
		std::memcpy(data, p.data, sizeof(data));
	}

	//给矩阵16个元素赋值
	void CMatrix::SetMatrix(float* p) {
		std::memcpy(data, p, sizeof(data));
	}

	void CMatrix::ToIndentity() {
		std::memset(data, 0, sizeof(data));
		data[0][0] = data[1][1] = data[2][2] = data[3][3];
	}

	//矩阵赋值
	CMatrix CMatrix::operator=(CMatrix& p) {
		std::memcpy(data, p.data, sizeof(data));
		return CMatrix(*this);
	}

	//矩阵数乘
	CMatrix CMatrix::operator*(float d)
	{
		CMatrix t;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				data[i][j] *= d;
			}
		}
		return t;
	}

	CMatrix operator*(const float num, CMatrix& p) {
		return p * num;
	}

	//矩阵相乘
	CMatrix CMatrix::operator*(CMatrix& p) {
		CMatrix t;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) {
				t[i][j] = 0;
				for (int num = 0; num < 4; ++num)
					t[i][j]+= data[num][j] * p[i][num];
			}
		return t;
	}

	//矩阵与向量相乘
	CVector CMatrix::vecMul(CVector& p) const
	{//补0
		float tmp[4] = { p[0],p[1],p[2],0 };
		float temp[4];
		for (int j = 0; j < 4; ++j) {
			temp[j] = 0;
			for (int num = 0; num < 4; ++num)
				temp[j] += data[num][j] * tmp[num];
		}
		CVector t(temp[0], temp[1], temp[2]);
		return t;
	}

	//矩阵与点相乘
	CVector CMatrix::posMul(CVector& p) const
	{//补1
		register float tmp0 = p[0], tmp1 = p[1], tmp2 = p[2], tmp3 = 1;
		float temp[4]{ 0 };
		register float t = 0;
		for (int j = 0; j < 4; ++j) {
			t = 0;
			t += data[0][j] * tmp0;
			t += data[1][j] * tmp1;
			t += data[2][j] * tmp2;
			t += data[3][j] * tmp3;
			temp[j] = t;
		}
		return CVector(temp[0], temp[1], temp[2]);
	}

	//设置为旋转矩阵
	void CMatrix::SetRotate(float seta, CVector axis) {
		axis.Normalize();//转为单位向量
		float COSSeta = cosf(seta / 180 * PI);
		float SINSeta = sinf(seta / 180 * PI);
		data[0][0] = axis.x * axis.x * (1 - COSSeta) + COSSeta;
		data[1][0] = axis.x * axis.y * (1 - COSSeta) - axis.z * SINSeta;
		data[2][0] = axis.x * axis.z * (1 - COSSeta) + axis.y * SINSeta;
		data[3][0] = 0;
		data[0][1] = axis.x * axis.y * (1 - COSSeta) + axis.z * SINSeta;
		data[1][1] = axis.y * axis.y * (1 - COSSeta) + COSSeta;
		data[2][1] = axis.z * axis.y * (1 - COSSeta) - axis.x * SINSeta;
		data[3][1] = 0;
		data[0][2] = axis.x * axis.z * (1 - COSSeta) - axis.y * SINSeta;
		data[1][2] = axis.z * axis.y * (1 - COSSeta) + axis.x * SINSeta;
		data[2][2] = axis.z * axis.z * (1 - COSSeta) + COSSeta;
		data[3][2] = 0;
		data[0][3] = 0;
		data[1][3] = 0;
		data[2][3] = 0;
		data[3][3] = 1;
	}

	//设置为平移矩阵
	void CMatrix::SetTrans(CVector trans) {
		data[0][0] = 1;
		data[0][1] = 0;
		data[0][2] = 0;
		data[0][3] = 0;
		data[1][0] = 0;
		data[1][1] = 1;
		data[1][2] = 0;
		data[1][3] = 0;
		data[2][0] = 0;
		data[2][1] = 0;
		data[2][2] = 1;
		data[2][3] = 0;
		data[3][0] = trans.x;
		data[3][1] = trans.y;
		data[3][2] = trans.z;
		data[3][3] = 1;
	}

	//设置为缩放矩阵
	void CMatrix::SetScale(CVector p) {
		data[0][0] = p.x;
		data[1][0] = 0;
		data[2][0] = 0;
		data[3][0] = 0;
		data[0][1] = 0;
		data[1][1] = p.y;
		data[2][1] = 0;
		data[3][1] = 0;
		data[0][2] = 0;
		data[1][2] = 0;
		data[2][2] = p.z;
		data[3][2] = 0;
		data[0][3] = 0;
		data[1][3] = 0;
		data[2][3] = 0;
		data[3][3] = 1;
	}

	float Det3(float* p) {
		return p[0 * 3 + 0] * (p[1 * 3 + 1] * p[2 * 3 + 2] - p[2 * 3 + 1] * p[1 * 3 + 2]) +
			p[1 * 3 + 0] * (p[2 * 3 + 1] * p[0 * 3 + 2] - p[0 * 3 + 1] * p[2 * 3 + 2]) +
			p[2 * 3 + 0] * (p[0 * 3 + 1] * p[1 * 3 + 2] - p[1 * 3 + 1] * p[0 * 3 + 2]);
	}
	//返回行列式的值
	float CMatrix::Det4() const
	{
		float det = 0;
		float p1[9] = {
			data[1][1],data[2][1],data[3][1],
			data[1][2],data[2][2],data[3][2],
			data[1][3],data[2][3],data[3][3],
		};
		float p2[9] = {
			data[0][1],data[2][1],data[3][1],
			data[0][2],data[2][2],data[3][2],
			data[0][3],data[2][3],data[3][3],
		};
		float p3[9] = {
			data[0][1],data[1][1],data[3][1],
			data[0][2],data[1][2],data[3][2],
			data[0][3],data[1][3],data[3][3],
		};
		float p4[9] = {
			data[0][1],data[1][1],data[2][1],
			data[0][2],data[1][2],data[2][2],
			data[0][3],data[1][3],data[2][3],
		};
		det = data[0][0] * Det3(p1) - data[1][0] * Det3(p2) + data[2][0] * Det3(p3) - data[3][0] * Det3(p4);
		return det;
	}

	//矩阵求逆，成功返回行列式的值，否则返回0，改变自身
	float CMatrix::Inverse() {
		float det = this->Det4();
		if (det == 0)
			return 0;
		CMatrix Adjoint_Matrix;

		float p[9];
		//i 行 ，j 列
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) {
				int r = 0, c = 0;
				for (int x = 0; x < 3; ++x) {
					for (int y = 0; y < 3; ++y) {
						if (r == i) {
							--x;
							break;
						}
						if (c == j) {
							++c;
							--y;
							continue;
						}
						p[x * 3 + y] = (*this)[c][r];
						++c;
					}
					++r;
					c = 0;
				}
				Adjoint_Matrix[i][j] = Det3(p) / det;
				Adjoint_Matrix[i][j] *= (i + j) % 2 == 1 ? -1 : 1;
			}

		*this = Adjoint_Matrix;
		return det;
	}

	//返回逆矩阵，不改变自身
	CMatrix CMatrix::GetInverse() {
		float det = this->Det4();
		CMatrix Adjoint_Matrix;
		float p[9];
		//i行 ，j列
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) {
				int r = 0, c = 0;
				for (int x = 0; x < 3; ++x) {
					for (int y = 0; y < 3; ++y) {
						if (r == i) {
							--x;
							break;
						}
						if (c == j) {
							++c;
							--y;
							continue;
						}
						p[x * 3 + y] = data[c][r];
						++c;
					}
					++r;
					c = 0;
				}
				Adjoint_Matrix[i][j] = Det3(p) / det;
				Adjoint_Matrix[i][j] *= (i + j) % 2 == 1 ? -1 : 1;
			}

		return Adjoint_Matrix;
	}

	//矩阵转欧拉角
	CEuler CMatrix::ToCEuler() {
		//float y = atan2f(*this[0 * 4 + 2], sqrtf(*this[1 * 4 + 2] * *this[1 * 4 + 2] + *this[2 * 4 + 2] * *this[2 * 4 + 2]));
		//float x = atan2f(*this[1 * 4 + 2], *this[2 * 4 + 2]);
		//float z = atan2f(*this[0 * 4 + 1], *this[0 * 4 + 0]);
		//return CEuler(x, y, z);
		CMatrix t = *this;
		float p = asinf(-t[2][1]);
		if (fabsf(cosf(p)) < 0.001f) {
			float h = atan2f(-t[0][2], t[0][0]);
			return CEuler(h / PI * 180, p / PI * 180, 0);
		}
		else {
			float h = atan2f(t[2][ 0], t[2][2]);
			float b = atan2f(t[0][1], t[1][1]);
			return CEuler(h / PI * 180, p / PI * 180, b / PI * 180);
		}
	}

	//矩阵转四元数
	CQuaternion CMatrix::ToCQuaternion() {
		CMatrix t = *this;
		float w = sqrtf(1 + t[0][0] + t[1][1] + t[2 ][2]) / 2;
		//w趋近于0
		if (fabs(w - 0) < 0.001f) {
			int flag = 0;
			if ((t[0][0] - t[1][1]) > 0.001f) {
				if ((t[0][0] - t[2][2]) > 0.001f) {
					flag = 0;//0最大
				}
				else {
					flag = 2;//2最大
				}
			}
			else {
				if ((t[2][2] - t[1][1]) > 0.001f) {
					flag = 2;//2最大
				}
				else {
					flag = 1;//1最大
				}
			}

			if (flag == 0) {
				float tmp = sqrtf(1 + t[0][0] - t[1][1] - t[2][2]);
				w = (t[1][2] - t[2][1]) / tmp;
				float x = tmp / 4;
				float y = (t[2][0] - t[0][2]) / tmp;
				float z = (t[1][0] - t[0][1]) / tmp;
				return CQuaternion(x, y, z, w);

			}
			else if (flag == 1) {
				float tmp = sqrtf(1 - t[0][0] + t[1][1] - t[2][2]);
				w = (t[2][0] - t[0][2]) / tmp;
				float x = (t[1][0] - t[0][1]) / tmp;
				float y = tmp / 4;
				float z = (t[1][2] - t[2][1]) / tmp;
				return CQuaternion(x, y, z, w);
			}
			else {
				float tmp = sqrtf(1 - t[0][0] - t[1][1] + t[2][2]);
				w = (t[0][1] - t[1][0]) / tmp;
				float x = (t[2][0] - t[0][2]) / tmp;
				float y = (t[2][1] - t[1][2]) / tmp;
				float z = tmp / 4;
				return CQuaternion(x, y, z, w);
			}
		}
		else {
			float x = (t[1][2] - t[2][1]) / (4 * w);
			float y = (t[2][0] - t[0][2]) / (4 * w);
			float z = (t[0][1] - t[1][0]) / (4 * w);
			return CQuaternion(x, y, z, w);
		}
	}

}
