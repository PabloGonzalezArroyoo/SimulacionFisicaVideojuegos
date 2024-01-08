#pragma once
#include "../../core.hpp"
#include <PxPhysicsAPI.h>
#include "../ecs/Manager.h"
#include "GameStateMachine.h"
#include <list>

using namespace physx;
using namespace std;

// Para evitar la dependencia circular
class GameStateMachine;
class GameState {
protected:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	// Flujo
	Manager* mng;
	GameStateMachine* gsm;

public:
	// Constructoras
	GameState() : gPhysics(nullptr), gScene(nullptr) {}
	GameState(GameStateMachine* gs, PxPhysics* ph, PxScene* sc) : gsm(gs), gPhysics(ph), gScene(sc) {};
	virtual ~GameState() {}

	// Métodos esenciales
	inline virtual void update(double t) { mng->update(t); }
	virtual void refresh() { mng->refresh(); mng->flushMessages(); }
	virtual void keyPressed(char key) {}
	virtual void keyReleased(char key) {}
};