#include "PlayState.h"

PlayState::PlayState(PxPhysics* ph, PxScene* sc) : GameState(ph, sc) {
	rbSys = new RigidBodySystem();
}

void PlayState::update(double t) {
	rbSys->update(t);
}