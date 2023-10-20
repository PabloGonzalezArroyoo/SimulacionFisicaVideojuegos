#pragma once

#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator {
private:
	// Velocidad
	uniform_real_distribution<float>* vX;
	uniform_real_distribution<float>* vY;
	uniform_real_distribution<float>* vZ;

	// Posición
	uniform_real_distribution<float>* pX;
	uniform_real_distribution<float>* pY;
	uniform_real_distribution<float>* pZ;

public:
	// Constructora y destructora
	UniformParticleGenerator(Vector3 iniPos, Vector3 var, float prob, Particle* m, bool st = true);
	virtual ~UniformParticleGenerator();

	// Método abstracto
	virtual list<Particle*> generateParticles();
};

