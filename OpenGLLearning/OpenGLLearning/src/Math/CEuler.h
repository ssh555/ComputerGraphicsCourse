#pragma once

namespace Math
{
	class CVector;
	class CMatrix;
	class CQuaternion;
#define PI 3.1415926f

	class CEuler
	{
	public:
		CEuler();
		CEuler(const float X, const float Y, const float Z);
		CEuler(const CEuler& vec);
		~CEuler();
		//偏航、俯仰、翻转
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
