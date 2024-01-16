#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:

public:
	PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc);

	virtual void update(double t);
	virtual void keyPressed(char key);
	virtual void keyReleased(char key);
};