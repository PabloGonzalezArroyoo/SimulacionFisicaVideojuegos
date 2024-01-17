#include "EndState.h"
#include "MainMenuState.h"

EndState::EndState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager(this, sc, ph);

	// Añadir sistema de rígidos
	mng->addSystem<TextSystem>();
	mng->addSystem<FireworkSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m.state_data.st = END_STATE;
	mng->send(m);
}

EndState::~EndState() {
	delete mng;
}

void EndState::update(double t) {
	GameState::update(t);
}

void EndState::keyPressed(char key) {
	switch (key) {
	case ' ':
		mng->getSystem<TextSystem>()->removeTexts();
		gsm->changeState(new MainMenuState(gsm, gPhysics, gScene));
		break;
	default: break;
	}
}