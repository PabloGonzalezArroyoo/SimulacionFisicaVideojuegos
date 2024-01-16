#include "PlayState.h"
#include "../../objects/systems/FloorSystem.h"
#include "../../objects/systems/TextSystem.h"
#include "../../objects/systems/JetpackSystem.h"
#include "../../objects/systems/ObstacleSystem.h"

PlayState::PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager(sc, ph);

	// Añadir sistema de rígidos
	mng->addSystem<JetpackSystem>();
	mng->addSystem<FloorSystem>();
	mng->addSystem<ObstacleSystem>();
	mng->addSystem<TextSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m.state_data.st = PLAY_STATE;
	mng->send(m);
}

void PlayState::update(double t) {
	GameState::update(t);
	mng->refresh();
}

void PlayState::keyPressed(char key) {
	mng->getSystem<JetpackSystem>()->keyPressed(key);
}

void PlayState::keyReleased(char key) {
	mng->getSystem<JetpackSystem>()->keyReleased(key);
}