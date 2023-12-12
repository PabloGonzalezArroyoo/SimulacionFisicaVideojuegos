#pragma once

//#include "../generators/rigids/GaussianRigidsGenerator.h"
#include "../physicObjects/RigidBody.h"

class RigidBodiesSystem {
private:

public:
	// Constructora y destructora
	RigidBodiesSystem(PxPhysics* gPhysics, PxScene* gScene);
	~RigidBodiesSystem();

	virtual void update(double t);
	virtual void keyPress(char c);
};