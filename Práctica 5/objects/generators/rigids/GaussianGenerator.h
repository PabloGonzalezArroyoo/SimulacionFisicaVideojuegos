#pragma once

#include "ActorGenerator.h"

class GaussianGenerator : public ActorGenerator {
protected:
	// Velocidad
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;

	// Posición
	normal_distribution<float>* pX = nullptr;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;

public:
	// Constructora y destructora
	GaussianGenerator(string n, Actor* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~GaussianGenerator();

	// Método abstracto
	virtual list<Actor*> generateParticles(double t);
};

