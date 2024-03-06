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
		//构造与析构
		CVector();
		CVector(const float X, const float Y, const float Z);
		CVector(const CVector& vec);
		~CVector();

		//重载操作符
		CVector operator+(const CVector& vec);//重载 + 操作符
		CVector operator-(const CVector& vec);
		CVector operator-();
		CVector operator=(const CVector& vec);//重载 = 操作符
		bool operator==(const CVector& vec);//重载 == 操作符
		bool operator!=(const CVector& vec);//重载 != 操作符

		friend CVector operator*(const float num, CVector& vec);//重载 * 操作符 向量数乘
		CVector operator*(const float num);

		//向量点乘
		float dotMul(const CVector& vec);
		//向量叉乘
		CVector crossMul(const CVector& vec);

		//向量单位化
		//改变自身
		void Normalize();
		//自身不变，返回单位化的值
		CVector Normalized();

		//向量求模
		float len();
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
