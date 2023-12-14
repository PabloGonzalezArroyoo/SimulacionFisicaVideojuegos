#pragma once

#include "../generators/rigids/GaussianGenerator.h"
#include "../generators/rigids/UniformGenerator.h"
#include "../physicObjects/RigidBody.h"
#include "../generators/forces/ForceGenerator.h"
#include "ForceRegistry.h"

class ActorSystem {
private:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	int rigidCounter = 0, rigidLimit = 20;
	RigidBody* floor;

	// Listas de objetos
	list<Actor*> _actors;
	list<ActorGenerator*> _actor_generators;

	// Vector de objetos a destruir
	vector<list<Actor*>::iterator> _actorsToDelete;

public:
	// Constructora y destructora
	ActorSystem(PxPhysics* gPhysics, PxScene* gScene);
	~ActorSystem();

	virtual void update(double t);
	virtual void keyPress(char c);

	void resetScene();
	void createGaussian(bool st);
	void createUniform(bool st);
};