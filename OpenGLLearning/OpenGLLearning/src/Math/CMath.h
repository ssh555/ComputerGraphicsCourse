#pragma once

#include <cmath>

namespace Engine
{
	class CMath
	{
	public:
		static constexpr float PI = 3.14159265358979323846f;

		// 返回x的绝对值
		static float Abs(float x) {
			return std::abs(x);
		}

		// 返回x的平方根
		static float Sqrt(float x) {
			return std::sqrt(x);
		}

		// 返回x的自然对数
		static float Log(float x) {
			return std::log(x);
		}

		// 返回以e为底的x的指数
		static float Exp(float x) {
			return std::exp(x);
		}

		// 返回x的以10为底的对数
		static float Log10(float x) {
			return std::log10(x);
		}

		// 返回x的n次幂
		static float Pow(float x, float n) {
			return std::pow(x, n);
		}

		// 返回x的正弦值
		static float Sin(float x) {
			return std::sin(x);
		}

		// 返回x的余弦值
		static float Cos(float x) {
			return std::cos(x);
		}

		// 返回x的正切值
		static float Tan(float x) {
			return std::tan(x);
		}

		// 返回x的反正弦值
		static float Asin(float x) {
			return std::asin(x);
		}

		// 返回x的反余弦值
		static float Acos(float x) {
			return std::acos(x);
		}

		// 返回x的反正切值
		static float Atan(float x) {
			return std::atan(x);
		}

		// 返回x和y的反正切值
		static float Atan2(float y, float x) {
			return std::atan2(y, x);
		}

		// 返回x和y的最大值
		static float Max(float x, float y) {
			return (x > y) ? x : y;
		}

		// 返回x和y的最小值
		static float Min(float x, float y) {
			return (x < y) ? x : y;
		}

		constexpr float radians(float degrees)
		{
			return degrees * 0.0174532925f; // 度到弧度的转换因子，约等于 Pi / 180
		}
	};
}
