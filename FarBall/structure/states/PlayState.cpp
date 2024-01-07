#include "PlayState.h"

PlayState::PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager();

	// Añadir sistema de rígidos
	mng->addSystem<RigidBodySystem>();
}

void PlayState::update(double t) {
	GameState::update(t);
}