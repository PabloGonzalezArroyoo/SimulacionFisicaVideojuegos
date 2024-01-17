#include "PlayState.h"
#include "EndState.h"
#include "../../objects/systems/FloorSystem.h"
#include "../../objects/systems/TextSystem.h"
#include "../../objects/systems/JetpackSystem.h"
#include "../../objects/systems/ObstacleSystem.h"

PlayState::PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc), fin(false) {
	// Crear manager del estado
	mng = new Manager(this, sc, ph);

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

PlayState::~PlayState() {
	delete mng;
}

void PlayState::update(double t) {
	GameState::update(t);
	mng->refresh();
	if (fin) gsm->changeState(new EndState(gsm, gPhysics, gScene));
}

void PlayState::keyPressed(char key) {
	if (key != '@') mng->getSystem<JetpackSystem>()->keyPressed(key);
	else fin = true;
}

void PlayState::keyReleased(char key) {
	mng->getSystem<JetpackSystem>()->keyReleased(key);
}
