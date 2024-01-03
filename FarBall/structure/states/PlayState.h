#pragma once
#include "GameState.h"
#include "../../objects/systems/RigidBodySystem.h"

class PlayState : public GameState {
private:
	RigidBodySystem* rbSys;

public:
	PlayState(PxPhysics* ph, PxScene* sc);

	virtual void update(double t);
};