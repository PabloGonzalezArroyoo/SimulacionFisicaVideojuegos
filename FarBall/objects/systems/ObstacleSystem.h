#pragma once

#include "../../structure/ecs/System.h"
#include "../physicObjects/RigidBody.h"

class ObstacleSystem : public System {
private:
	Vector3 posBg, posFg;
	int prevPenX;
	
public:
	constexpr static sysId_type id = _sys_OBSTACLES;

	virtual void initSystem();
	virtual void update(double t);

	void createBgObject(int x);
};

