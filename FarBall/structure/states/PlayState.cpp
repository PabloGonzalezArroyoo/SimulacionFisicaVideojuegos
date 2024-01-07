#include "PlayState.h"

PlayState::PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager();

	// A�adir sistema de r�gidos
	mng->addSystem<RigidBodySystem>();
}

void PlayState::update(double t) {
	GameState::update(t);
}