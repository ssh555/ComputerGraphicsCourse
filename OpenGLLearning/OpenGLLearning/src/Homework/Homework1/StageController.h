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
	// 创建Stage
	void CreateStage();

private:
	// 创建棋盘面
	void CreatePlain();

	// 创建A区
	void CreateAStage();

	// 创建B区
	void CreateBStage();

	// 创建C区
	void CreateCStage();

	// 绑定输入 -> 
	// 1 -> 切换Stage配色
	// 2 -> 切换Stage绕中心轴旋转|暂停
	void BindInput();

	void SwitchStageColor(bool colorState);

	// 初始化配置Stage配色
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

	// 是否正在旋转
	bool m_isRotating = false;
	// 旋转度数/s
	float m_rotRate = 30;
	// 当前使用配色
	// false -> 1
	// true -> 2
	bool m_colorState = false;


};

