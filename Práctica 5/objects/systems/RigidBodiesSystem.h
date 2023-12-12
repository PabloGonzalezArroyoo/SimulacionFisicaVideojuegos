#pragma once

#include "../generators/rigids/GaussianRigidGenerator.h"
#include "../physicObjects/RigidBody.h"

class RigidBodiesSystem {
private:
	// Listas de objetos
	list<RigidBody*> _rigidBodies;
	list<RigidGenerator*> _rigid_generators;

	// Vector de objetos a destruir
	vector<list<RigidBody*>::iterator> _rigidsToDelete;

public:
	// Constructora y destructora
	RigidBodiesSystem(PxPhysics* gPhysics, PxScene* gScene);
	~RigidBodiesSystem();

	virtual void update(double t);
	virtual void keyPress(char c);
};