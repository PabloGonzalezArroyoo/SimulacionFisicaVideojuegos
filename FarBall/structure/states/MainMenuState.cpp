#include "MainMenuState.h"
#include "PlayState.h"

MainMenuState::MainMenuState(GameStateMachine* g, PxPhysics* ph, PxScene* sc) : GameState(g, ph, sc) {
	// Crear manager del estado
	mng = new Manager();

	// A�adir sistema de r�gidos
	mng->addSystem<TextSystem>();
}

//void MainMenuState::update(double t) {
//	GameState::update(t);
//}

void MainMenuState::keyPressed(char key) {
	switch (key) {
		case ' ': 
			gsm->changeState(new PlayState(gsm, gPhysics, gScene));
			break;
		default: break;
	}
}