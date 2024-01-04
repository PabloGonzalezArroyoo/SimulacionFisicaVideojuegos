#pragma once
#include "../physicObjects/RigidBody.h"

class RigidBodySystem {
private:

	RigidBody* floor = nullptr;

public:
	void initSystem();

	void update(double t);

	inline void addFloor() {
		/*if (floor == nullptr) floor = new RigidBody(gPhysics, gScene, PxTransform(Vector3(-20)),
			CreateShape(PxBoxGeometry(400, 2, 400)), NONE, colors[BLUE], 1000, false);*/
	}
};

