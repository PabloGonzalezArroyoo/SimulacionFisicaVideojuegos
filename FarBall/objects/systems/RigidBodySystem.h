#pragma once
#include "../../structure/ecs/System.h"

class RigidBodySystem : public System {
private:

public:
	void initSystem();

	void update(double t);
};

