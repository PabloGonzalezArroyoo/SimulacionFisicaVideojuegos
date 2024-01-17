#pragma once

#include "../../structure/ecs/System.h"
#include "../physicObjects/RigidBody.h"
#include "../gameObjects/Rings.h"
#include <queue>

class ObstacleSystem : public System {
private:
	// Posiciones
	Vector3 posBg, posFg, posRings;
	int prevPenXBg, prevPenXRings;

	// Anillos y generadores
	list<Rings*> rings;
	vector<list<Rings*>::iterator> ringsToDelete;
	queue<ForceGenerator*> generators;

public:
	constexpr static sysId_type id = _sys_OBSTACLES;

	// M�todos virtuales
	virtual void initSystem();
	virtual void update(double t);

	// M�todos propios
	void createBgObject(int x);
	void createRing(int x);
};

