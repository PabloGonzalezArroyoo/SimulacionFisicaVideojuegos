#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager(this, sc, ph);

	// Añadir sistema de rígidos
	mng->addSystem<TextSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m.state_data.st = MAINMENU_STATE;
	mng->send(m);
}

MainMenuState::~MainMenuState() {
	delete mng;
}

void MainMenuState::update(double t) {
	GameState::update(t);
}

void MainMenuState::keyPressed(char key) {
	switch (key) {
		case ' ': gsm->changeState(new PlayState(gsm, gPhysics, gScene)); break;
		default: break;
	}
}