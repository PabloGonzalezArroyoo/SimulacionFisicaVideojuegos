#pragma once
#include "../../core.hpp"
#include <PxPhysicsAPI.h>
#include "../../objects/physicObjects/Actor.h"
#include <list>

using namespace physx;
using namespace std;

// Para evitar la dependencia circular
class GameState {
protected:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	// Objetos
	list<Actor*> objects;

public:
	// Constructoras
	GameState() : gPhysics(nullptr), gScene(nullptr) {}
	GameState(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc) {};
	virtual ~GameState() {}

	// Métodos esenciales
	inline virtual void update(double t) {}
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
};