#pragma once
#include "../ecs/Manager.h"
#include "../../core.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

// Para evitar la dependencia circular
class GameState {
protected:
	Manager* mng;
	PxPhysics* gPhysics;
	PxScene* gScene;

public:
	// Constructoras
	GameState() : gPhysics(nullptr), gScene(nullptr) {}
	GameState(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc) {};
	virtual ~GameState() {}

	// Métodos esenciales
	inline virtual void update(double t) { mng->update(t); }
	inline virtual void refresh() { mng->refresh(); }
	virtual void keyPressed(int key) { }
	virtual void keyReleased(int key) { }
};