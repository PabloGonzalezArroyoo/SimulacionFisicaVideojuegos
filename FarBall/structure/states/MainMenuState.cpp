#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager();

	// Añadir sistema de rígidos
	mng->addSystem<TextSystem>()->setState(MAINMENU_STATE);
}

void MainMenuState::update(double t) {
	GameState::update(t);
}

void MainMenuState::keyPressed(char key) {
	switch (key) {
		case ' ': 
			mng->getSystem<TextSystem>()->removeTexts();
			gsm->changeState(new PlayState(gsm, gPhysics, gScene));
			break;
		default: break;
	}
}