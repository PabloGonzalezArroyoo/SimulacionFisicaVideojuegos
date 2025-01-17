#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator {
protected:
	// Velocidad
	uniform_real_distribution<float>* vX;
	uniform_real_distribution<float>* vY;
	uniform_real_distribution<float>* vZ;

	// Posici�n
	uniform_real_distribution<float>* pX;
	uniform_real_distribution<float>* pY;
	uniform_real_distribution<float>* pZ;

public:
	// Constructora y destructora
	UniformParticleGenerator(string n, Particle* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~UniformParticleGenerator();

	// M�todo abstracto
	virtual list<Particle*> generateParticles(double t);
};

