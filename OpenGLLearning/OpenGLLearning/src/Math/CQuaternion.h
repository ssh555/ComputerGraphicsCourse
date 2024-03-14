#pragma once

namespace Engine
{
	class CVector;
	class CEuler;
	class CMatrix;

	class CQuaternion
	{
	public:
		CQuaternion quatLookAt(const CVector& direction, const CVector& up);


	public:
		CQuaternion();
		CQuaternion(const float X, const float Y, const float Z, const float W);
		CQuaternion(const float W, const CVector& vec);
		CQuaternion(const CQuaternion& vec);
		~CQuaternion();

		float x, y, z, w;
		void Set(float x, float y, float z, float w);

		//四元数设置
		void SetAngle(float angle, CVector axis);
		//重载赋值
		CQuaternion& operator=(const CQuaternion& p);
		//重载 +
		CQuaternion operator+(const CQuaternion& p);
		//重载 -
		CQuaternion operator-(const CQuaternion& p);
		//重载 ==
		bool operator==(const CQuaternion& p);
		//重载数乘
		CQuaternion operator*(float data);
		friend CQuaternion operator*(float data, CQuaternion& n);
		//幂
		CQuaternion operator^(float t);
		//四元数乘法 叉乘
		CQuaternion operator*(const CQuaternion& p);
		//点乘
		float dotMul(const CQuaternion& p);
		//求模
		float len();
		//标准化
		bool Normalize();
		//返回共轭四元数
		CQuaternion GetConjugate();
		//求逆 改变自身
		CQuaternion& Inverse();
		//求逆 不改变自身
		CQuaternion GetInverse();
		//求差
		CQuaternion Div(const CQuaternion& b);
		//求旋转角和角度
		void GetAngle(float& angle, CVector& axis);
		//插值。从当前四元数插值到Vend四元数,t是参数[0,1]
		CQuaternion Slerp(const CQuaternion& vend, float t);
		//插值。一次插值出n个数据。插值参数保存在数组t中，结果返回到数组Result中。
		void Slerp(const CQuaternion& vend, int n, float* t, CQuaternion* Result);

		//四元数转欧拉角
		CEuler ToCEuler();
		//四元数转矩阵
		CMatrix ToCMatrix();

		operator float* () { return &x; };

	private:

	};

}
