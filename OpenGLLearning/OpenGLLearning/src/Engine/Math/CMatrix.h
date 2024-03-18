#pragma once
#include <iostream>
namespace Engine
{
	class CEuler;
	class CQuaternion;
	class CVector;

	class CMatrix
	{
	public:
		// 静态函数，用于创建正交投影矩阵
		static CMatrix ortho(float left, float right, float bottom, float top, float nearVal, float farVal);
		// 静态函数，用于创建平移矩阵
		static CMatrix translate(const CMatrix& matrix, float x, float y, float z);
		static CMatrix translate(const CMatrix& matrix, const CVector& vec);
		static CMatrix scale(const CMatrix& matrix, float scaleX, float scaleY, float scaleZ);
		static CMatrix scale(const CMatrix& matrix, const CVector& vec);
		static CMatrix perspective(float fov, float aspectRatio, float nearVal, float farVal);
		static CMatrix lookAt(const CVector& eye, const CVector& center, const CVector& up);


	public:
		CMatrix();
		CMatrix(float* p);
		CMatrix(const CMatrix& p);
		// 构造函数，用于创建指定值的矩阵
		CMatrix(float value);
		~CMatrix();




		//给矩阵16个元素赋值
		void SetMatrix(float* p);
		//矩阵赋值
		CMatrix& operator=(const CMatrix& p);
		//矩阵数乘
		CMatrix operator*(float d);
		friend CMatrix operator*(const float num, CMatrix& p);//重载 * 操作符 向量数乘
		//矩阵相乘
		CMatrix operator*(const CMatrix& p) const;
		CMatrix& operator*=(const CMatrix& p);
		//矩阵与向量相乘
		CVector vecMul(CVector& p) const;
		//矩阵与点相乘
		CVector posMul(CVector& p) const;
		//设置为旋转矩阵
		void SetRotate(float seta, CVector axis);
		//设置为平移矩阵
		void SetTrans(CVector trans);
		//设置为缩放矩阵
		void SetScale(CVector p);
		//矩阵求逆，成功返回行列式的值，否则返回0，改变自身
		float Inverse();
		//返回逆矩阵，不改变自身
		CMatrix GetInverse();
		//变化为单位矩阵
		void ToIndentity();

		//返回行列式的值
		float Det4() const;

		//矩阵转欧拉角
		CEuler ToCEuler();
		//矩阵转四元数
		CQuaternion ToCQuaternion();

		//operator float* () {
		//	return &m00;
		//}
		// 重载[]运算符，用于访问矩阵元素
		float* operator[](int index) {
			return data[index];
		}
		// 重载[]运算符，用于访问矩阵元素（const 重载）
		const float* operator[](int index) const {
			return data[index];
		}
		// 重载&运算符，用于获取矩阵元素的地址
		float* operator&() {
			return &data[0][0];
		}

		// 打印矩阵的值
		void PrintMatrix() const {
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					std::cout << data[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}

	private:
		//float m00, m10, m20, m30;
		//float m01, m11, m21, m31;
		//float m02, m12, m22, m32;
		//float m03, m13, m23, m33;

		float data[4][4];
	};


}
