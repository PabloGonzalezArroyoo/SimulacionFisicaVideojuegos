#pragma once
#include "GameState.h"
#include "../../objects/systems/TextSystem.h"
#include "../../objects/systems/FireworkSystem.h"

class EndState : public GameState {
private:

public:
	// Constructora
	EndState(GameStateMachine* g, PxPhysics* ph, PxScene* sc);
	~EndState();

	// Sobrecarga del método update
	virtual void update(double t);
	virtual void keyPressed(char key);
};