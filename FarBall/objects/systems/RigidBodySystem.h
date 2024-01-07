#pragma once
#include "../../structure/states/GameState.h"
#include "../physicObjects/RigidBody.h"
#include "../../structure/ecs/System.h"

class RigidBodySystem : public System {
private:

	GameState* gst;
	RigidBody* floor = nullptr;

public:
	constexpr static sysId_type id = _sys_RIGIDBODY;

	RigidBodySystem(GameState* g) : System(), gst(g) {};

	void initSystem();

	void update(double t);

	inline void addFloor() {
		/*if (floor == nullptr) floor = new RigidBody(gPhysics, gScene, PxTransform(Vector3(-20)),
			CreateShape(PxBoxGeometry(400, 2, 400)), NONE, colors[BLUE], 1000, false);*/
	}
};

