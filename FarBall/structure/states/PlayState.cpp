#include "PlayState.h"
#include "../../objects/systems/FloorSystem.h"
#include "../../objects/systems/TextSystem.h"
#include "../../objects/systems/PenguinSystem.h"

PlayState::PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager(sc, ph);

	// Añadir sistema de rígidos
	mng->addSystem<TextSystem>();
	FloorSystem* flSys = mng->addSystem<FloorSystem>();
	PenguinSystem* pnSys = mng->addSystem<PenguinSystem>();
	flSys->setPenguin(pnSys->getPenguin());

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m.state_data.st = PLAY_STATE;
	mng->send(m);
}

void PlayState::update(double t) {
	GameState::update(t);
}

void PlayState::keyPressed(char key) {
	switch (key) {
		case 'I': case 'K':
			mng->getSystem<PenguinSystem>()->keyPressed(key);
			break;
	}
}