#pragma once

#include "../generators/rigids/GaussianRigidsGenerator.h"

class RigidBodiesSystem {
private:

public:
	// Constructora y destructora
	RigidBodiesSystem();
	~RigidBodiesSystem();

	virtual void update(double t);
	virtual void keyPress(char c);
};