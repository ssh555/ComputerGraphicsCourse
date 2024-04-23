#pragma once
#include "CMath.h"
#include <iostream>
#include <sstream>

namespace Engine
{
	class CVector;
	class CMatrix;
	class CQuaternion;

	class CEuler
	{
	public:
		CEuler();
		CEuler(const float X, const float Y, const float Z);
		CEuler(const CEuler& vec);

		CEuler(const std::string& str)
		{
			auto strs = CMath::split(str, ',');
			h = CMath::stringToNum<float>(strs[0]);
			p = CMath::stringToNum<float>(strs[1]);
			b = CMath::stringToNum<float>(strs[2]);
		}
		// 重载输出操作符 <<
		friend std::ostream& operator<<(std::ostream& os, const CEuler& vec)
		{
			os << vec.h << "," << vec.p << "," << vec.b;
			return os;
		}

		~CEuler();
		//偏航、俯仰、翻转
		// y, x, z
		float h, p, b;
		//设置角的值
		void Set(float h, float p, float b);

		//欧拉角转换为向量
		//如果传入updir指针不为0，则输出向量同时输出上方向量到updir中
		CVector ToCVector(CVector* updir = 0);

		//欧拉角转矩阵
		CMatrix ToCMatrix();

		//欧拉角转四元数
		CQuaternion ToQuaternion();

		//欧拉角规范化
		void Normal();

		operator float* () { return &h; }


	private:

	};

}
