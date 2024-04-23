#pragma once
#include "tests/Test.h"
#include "Engine/Math/CEuler.h"
using namespace test;

class CameraController;

class CameraControllerUI : public Test
{

public:
	CameraControllerUI();

	virtual void OnImGuiRender() override;

	CameraController* controller;

	Engine::CEuler rot;
};

