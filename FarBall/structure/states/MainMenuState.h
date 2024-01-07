#pragma once
#include "GameState.h"
#include "../../objects/systems/TextSystem.h"

class MainMenuState : public GameState {
private:

public:
	// Constructora
	MainMenuState(GameStateMachine* g, PxPhysics* ph, PxScene* sc);

	// Sobrecarga del m�todo update
	virtual void update(double t);
	virtual void keyPressed(char key);
};