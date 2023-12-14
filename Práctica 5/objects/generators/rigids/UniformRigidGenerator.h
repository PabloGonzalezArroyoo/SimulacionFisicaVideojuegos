#pragma once

#include "RigidGenerator.h"

class UniformRigidGenerator : public RigidGenerator {
protected:
	// Velocidad
	uniform_real_distribution<float>* vX;
	uniform_real_distribution<float>* vY;
	uniform_real_distribution<float>* vZ;

	// Posición
	uniform_real_distribution<float>* pX = nullptr;
	uniform_real_distribution<float>* pY;
	uniform_real_distribution<float>* pZ;

public:
	// Constructora y destructora
	UniformRigidGenerator(string n, RigidBody* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~UniformRigidGenerator();

	// Método abstracto
	virtual list<RigidBody*> generateParticles(double t);
};

