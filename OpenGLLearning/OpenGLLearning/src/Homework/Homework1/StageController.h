#pragma once
#include "Engine/Component/Component.h"
#include <vector>
#include "Engine/Math/CVector.h"


namespace Engine
{
	class GameObject;
	class CVector;
}

using namespace Engine;

class StageController : Component
{
	friend class Stage;
	friend class GameObject;

protected:
	StageController(GameObject* obj);
	virtual ~StageController();

	virtual void Tick(float deltatime) override;

private:
	// ����Stage
	void CreateStage();

private:
	// ����������
	void CreatePlain();

	// ����A��
	void CreateAStage();

	// ����B��
	void CreateBStage();

	// ����C��
	void CreateCStage();

	// ������ -> 
	// 1 -> �л�Stage��ɫ
	// 2 -> �л�Stage����������ת|��ͣ
	void BindInput();

	void SwitchStageColor(bool colorState);

	// ��ʼ������Stage��ɫ
	void InitStageColor();

	GameObject* CreateCube();

private:
	struct StageColor
	{
		CVector color[2];
	};

	GameObject* m_plain;

	std::vector<GameObject*> m_AStage;
	StageColor m_AColor;

	std::vector<GameObject*> m_B1Stage;
	StageColor m_B1Color;

	std::vector<GameObject*> m_B2Stage;
	StageColor m_B2Color;

	std::vector<GameObject*> m_BTStage;
	StageColor m_BTColor;

	std::vector<GameObject*> m_CStage;
	StageColor m_CColor;

	// �Ƿ�������ת
	bool m_isRotating = false;
	// ��ת����/s
	float m_rotRate = 30;
	// ��ǰʹ����ɫ
	// false -> 1
	// true -> 2
	bool m_colorState = false;


};

