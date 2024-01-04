#pragma once
#include "GameState.h"
#include "../../objects/systems/RigidBodySystem.h"

class PlayState : public GameState {
private:
	RigidBodySystem* rbSys;
	RigidBody* floor = nullptr;

public:
	PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc);

	virtual void update(double t);

	inline void addFloor() {
		if (floor == nullptr) floor = new RigidBody(gPhysics, gScene, PxTransform(Vector3(-20)),
			CreateShape(PxBoxGeometry(400, 2, 400)), NONE, colors[BLUE], 1000, false);
	}
};