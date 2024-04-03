#pragma once
#include <math.h>
#include <iostream>
#include <array>

namespace Engine
{
	using namespace std;
	class CEuler;
	class CQuaternion;

	class CVector
	{
	public:
		// 静态成员函数，返回向上的单位向量
		static CVector Up() {
			return CVector(0.0f, 1.0f, 0.0f);
		}

		// 静态成员函数，返回向下的单位向量
		static CVector Down() {
			return CVector(0.0f, -1.0f, 0.0f);
		}

		// 静态成员函数，返回向左的单位向量
		static CVector Left() {
			return CVector(1.0f, 0.0f, 0.0f);
		}

		// 静态成员函数，返回向右的单位向量
		static CVector Right() {
			return CVector(-1.0f, 0.0f, 0.0f);
		}

		// 静态成员函数，返回向前的单位向量
		static CVector Forward() {
			return CVector(0.0f, 0.0f, 1.0f);
		}

		// 静态成员函数，返回向后的单位向量
		static CVector Backward() {
			return CVector(0.0f, 0.0f, -1.0f);
		}

		static CVector Zero() {
			return CVector(0.0f, 0.0f, 0.0f);
		}

		static CVector One() {
			return CVector(1.0f, 1.0f, 1.0f);
		}
		static float Angle(const CVector& vec1, const CVector& vec2)
		{
			// 先将向量单位化
			CVector normalizedVec1 = vec1.Normalized();
			CVector normalizedVec2 = vec2.Normalized();

			// 计算点乘
			float dotProduct = normalizedVec1.dotMul(normalizedVec2);

			// 由于浮点数精度问题，点乘结果可能略大于 1 或略小于 -1
			// 因此需要将其限制在 [-1, 1] 范围内
			dotProduct = fmaxf(fminf(dotProduct, 1.0f), -1.0f);

			// 使用反余弦函数计算夹角
			return acosf(dotProduct);
		}

	public:
		//构造与析构
		CVector();
		CVector(const float X, const float Y, const float Z);
		CVector(const CVector& vec);
		~CVector();

		//重载操作符
		CVector operator+(const CVector& vec);//重载 + 操作符
		CVector operator+(const CVector& vec) const;//重载 + 操作符
		CVector operator-(const CVector& vec);
		CVector operator-(const CVector& vec) const;
		CVector operator-();
		CVector operator=(const CVector& vec);//重载 = 操作符
		bool operator==(const CVector& vec);//重载 == 操作符
		bool operator!=(const CVector& vec);//重载 != 操作符

		friend CVector operator*(const float num, CVector& vec);//重载 * 操作符 向量数乘
		CVector operator*(const float num);
		CVector operator*(const float num) const;
		float operator*(const CVector& vec);
		CVector operator*(const CQuaternion& rot);
		CVector operator/(const CVector& vec);
		CVector& operator+=(const CVector& vec);
		bool operator!=(const std::array<float, 3>& otherArray) const;
		friend bool operator!=(const std::array<float, 3>& array, const CVector& vector);

		//向量点乘
		float dotMul(const CVector& vec);
		float dotMul(const CVector& vec) const;
		//向量叉乘
		CVector crossMul(const CVector& vec) const;
		CVector crossMul(const CVector& vec);

		//向量单位化
		//改变自身
		void Normalize();
		//自身不变，返回单位化的值
		CVector Normalized() const;

		//向量求模
		float len() const;
		//向量投影
		CVector project(CVector& vec);
		//绕轴旋转
		CVector RotateAxis(CVector& axis, float angle);

		//设置向量值
		void SetVec(float X, float Y, float Z);

		//向量转为欧拉角
		CEuler ToCEuler();

		operator float* () { return &x; }	//自动类型转换

		//向量(x,y,z)
		float x;
		float y;
		float z;
	};

}
