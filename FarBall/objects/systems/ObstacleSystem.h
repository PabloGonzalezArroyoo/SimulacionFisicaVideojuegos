#pragma once

#include "../../structure/ecs/System.h"
#include "../physicObjects/RigidBody.h"
#include "../gameObjects/Rings.h"

enum ObstacleType {
	TINY, MEDIUM, BIG, 
};

class ObstacleSystem : public System {
private:
	Vector3 posBg, posFg, posRings;
	int prevPenXBg, prevPenXRings;
	list<Rings*> rings;
	vector<list<Rings*>::iterator> ringsToDelete;

public:
	constexpr static sysId_type id = _sys_OBSTACLES;

	virtual void initSystem();
	virtual void update(double t);

	void createBgObject(int x);
	void createRing(int x);
};

