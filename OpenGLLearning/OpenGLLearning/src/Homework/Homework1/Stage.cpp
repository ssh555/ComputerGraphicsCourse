#include "Stage.h"
#include "StageController.h"

Stage::Stage()
{
	auto controller = this->AddComponent<StageController>();
}
