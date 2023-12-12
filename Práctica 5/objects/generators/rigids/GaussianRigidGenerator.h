#pragma once

#include "RigidGenerator.h"

class GaussianRigidGenerator : public RigidGenerator {
protected:
	// Velocidad
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;

	// Posición
	normal_distribution<float>* pX;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;

public:
	// Constructora y destructora
	GaussianRigidGenerator(string n, RigidBody* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~GaussianRigidGenerator();

	// Método abstracto
	virtual list<RigidBody*> generateParticles(double t);
};

