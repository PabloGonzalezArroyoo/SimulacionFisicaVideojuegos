#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:
	bool fin;

public:
	PlayState(GameStateMachine* g, PxPhysics* ph, PxScene* sc);
	~PlayState();

	virtual void update(double t);
	virtual void keyPressed(char key);
	virtual void keyReleased(char key);
};