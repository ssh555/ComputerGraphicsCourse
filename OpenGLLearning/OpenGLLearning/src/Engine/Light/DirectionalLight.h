#pragma once
#include "../GameObject/GameObject.h"
#include "../Math/CVector.h"


namespace Engine
{
	class GameObject;
	class CVector;

	// �ݶ�Ϊֻ��һ��ȫ�ֵ�ֱ�߹���
	class DirectionalLight : public GameObject // ʹ�ù��м̳�
	{
		friend class GlobalManager;
	private:
		// ˽�й��캯������ֹ�����ⲿ��ʵ����
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
