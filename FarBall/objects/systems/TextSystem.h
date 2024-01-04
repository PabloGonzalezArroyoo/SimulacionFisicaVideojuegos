#pragma once
#include "../../structure/states/GameState.h"
#include "../../structure/ecs/System.h"

class TextSystem : public System {
private:
	GameState* gst;

public:
	constexpr static sysId_type id = _sys_RIGIDBODY;

	void initSystem();

	void update(double t);
};