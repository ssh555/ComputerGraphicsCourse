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
		// ��̬���������ڴ�������ͶӰ����
		static CMatrix ortho(float left, float right, float bottom, float top, float nearVal, float farVal);
		// ��̬���������ڴ���ƽ�ƾ���
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
		// ���캯�������ڴ���ָ��ֵ�ľ���
		CMatrix(float value);
		~CMatrix();




		//������16��Ԫ�ظ�ֵ
		void SetMatrix(float* p);
		//����ֵ
		CMatrix& operator=(const CMatrix& p);
		//��������
		CMatrix operator*(float d);
		friend CMatrix operator*(const float num, CMatrix& p);//���� * ������ ��������
		//�������
		CMatrix operator*(const CMatrix& p) const;
		CMatrix& operator*=(const CMatrix& p);
		//�������������
		CVector vecMul(CVector& p) const;
		//����������
		CVector posMul(CVector& p) const;
		//����Ϊ��ת����
		void SetRotate(float seta, CVector axis);
		//����Ϊƽ�ƾ���
		void SetTrans(CVector trans);
		//����Ϊ���ž���
		void SetScale(CVector p);
		//�������棬�ɹ���������ʽ��ֵ�����򷵻�0���ı�����
		float Inverse();
		//��������󣬲��ı�����
		CMatrix GetInverse();
		//�仯Ϊ��λ����
		void ToIndentity();

		//��������ʽ��ֵ
		float Det4() const;

		//����תŷ����
		CEuler ToCEuler();
		//����ת��Ԫ��
		CQuaternion ToCQuaternion();

		//operator float* () {
		//	return &m00;
		//}
		// ����[]����������ڷ��ʾ���Ԫ��
		float* operator[](int index) {
			return data[index];
		}
		// ����[]����������ڷ��ʾ���Ԫ�أ�const ���أ�
		const float* operator[](int index) const {
			return data[index];
		}
		// ����&����������ڻ�ȡ����Ԫ�صĵ�ַ
		float* operator&() {
			return &data[0][0];
		}

		// ��ӡ�����ֵ
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
