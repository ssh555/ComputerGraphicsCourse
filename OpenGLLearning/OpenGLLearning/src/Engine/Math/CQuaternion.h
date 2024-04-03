#pragma once
#include <string>
#include <sstream>
#include "CMath.h"

namespace Engine
{
	class CVector;
	class CEuler;
	class CMatrix;

	class CQuaternion
	{


	public:
		static CQuaternion quatLookAt(const CVector& direction, const CVector& up);
		static CQuaternion Identity()
		{
			return CQuaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}
		static CQuaternion quatFromAxisAngle(const CVector& axis, float angle);
		static CQuaternion quatFromMatrix(const CMatrix& newTransform);

	public:
		CQuaternion();
		CQuaternion(const float X, const float Y, const float Z, const float W);
		CQuaternion(const float W, const CVector& vec);
		CQuaternion(const CQuaternion& vec);
		CQuaternion(const std::string& str)
		{
			auto strs = CMath::split(str, ',');
			x = CMath::stringToNum<float>(strs[0]);
			y = CMath::stringToNum<float>(strs[1]);
			z = CMath::stringToNum<float>(strs[2]);
			w = CMath::stringToNum<float>(strs[2]);
		}
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
		// 重载输出操作符 <<
		friend std::ostream& operator<<(std::ostream& os, const CQuaternion& q)
		{
			os << q.x << "," << q.y << "," << q.z << "," << q.w;
			return os;
		}
		friend std::istream& operator>>(std::istream& is, CQuaternion& q)
		{
			std::string str;
			is >> str;
			auto strs = CMath::split(str, ',');
			q.x = CMath::stringToNum<float>(strs[0]);
			q.y = CMath::stringToNum<float>(strs[1]);
			q.z = CMath::stringToNum<float>(strs[2]);
			q.w = CMath::stringToNum<float>(strs[3]);
			return is;
		}
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
		CVector operator*(const CVector& vec);
		CVector operator*(const CVector& vec) const;

		//四元数转欧拉角
		CEuler ToCEuler();
		//四元数转矩阵
		CMatrix ToCMatrix();

		operator float* () { return &x; };

		CVector GetVectorPart();

	private:

	};

}
