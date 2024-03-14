#pragma once

#include <cmath>

namespace Engine
{
	class CMath
	{
	public:
		static constexpr float PI = 3.14159265358979323846f;

		// ����x�ľ���ֵ
		static float Abs(float x) {
			return std::abs(x);
		}

		// ����x��ƽ����
		static float Sqrt(float x) {
			return std::sqrt(x);
		}

		// ����x����Ȼ����
		static float Log(float x) {
			return std::log(x);
		}

		// ������eΪ�׵�x��ָ��
		static float Exp(float x) {
			return std::exp(x);
		}

		// ����x����10Ϊ�׵Ķ���
		static float Log10(float x) {
			return std::log10(x);
		}

		// ����x��n����
		static float Pow(float x, float n) {
			return std::pow(x, n);
		}

		// ����x������ֵ
		static float Sin(float x) {
			return std::sin(x);
		}

		// ����x������ֵ
		static float Cos(float x) {
			return std::cos(x);
		}

		// ����x������ֵ
		static float Tan(float x) {
			return std::tan(x);
		}

		// ����x�ķ�����ֵ
		static float Asin(float x) {
			return std::asin(x);
		}

		// ����x�ķ�����ֵ
		static float Acos(float x) {
			return std::acos(x);
		}

		// ����x�ķ�����ֵ
		static float Atan(float x) {
			return std::atan(x);
		}

		// ����x��y�ķ�����ֵ
		static float Atan2(float y, float x) {
			return std::atan2(y, x);
		}

		// ����x��y�����ֵ
		static float Max(float x, float y) {
			return (x > y) ? x : y;
		}

		// ����x��y����Сֵ
		static float Min(float x, float y) {
			return (x < y) ? x : y;
		}

		constexpr float radians(float degrees)
		{
			return degrees * 0.0174532925f; // �ȵ����ȵ�ת�����ӣ�Լ���� Pi / 180
		}
	};
}
