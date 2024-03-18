#pragma once
#include "../GameObject/GameObject.h"
#include "../Math/CVector.h"


namespace Engine
{
	class GameObject;
	class CVector;

	// 暂定为只有一个全局的直线光照
	class DirectionalLight : public GameObject // 使用公有继承
	{
		friend class GlobalManager;
	private:
		// 私有构造函数，防止类在外部被实例化
		DirectionalLight() : m_intensity(1.0f), m_lightcolor(CVector(1.0f, 1.0f, 1.0f)){}

	public:
		float GetIntensity() const { return m_intensity; }
		void SetIntensity(float intensity) { m_intensity = intensity; }
		const CVector& GetLightColor() const { return m_lightcolor; }
		void SetLightColor(const CVector& color) { m_lightcolor = color; }

	private:
		float m_intensity;
		CVector m_lightcolor;
	};
}
