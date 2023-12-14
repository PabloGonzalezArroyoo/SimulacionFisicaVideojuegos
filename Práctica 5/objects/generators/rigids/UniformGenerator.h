#pragma once

#include "RigidGenerator.h"

class UniformGenerator : public ActorGenerator {
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
	UniformGenerator(string n, Actor* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~UniformGenerator();

	// Método abstracto
	virtual list<Actor*> generateParticles(double t);
};

