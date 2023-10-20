#pragma once

#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
private:
	// Velocidad
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;

	// Posici�n
	normal_distribution<float>* pX;
	normal_distribution<float>* pY;
	normal_distribution<float>* pZ;


public:
	// Constructora y destructora
	GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, Particle* m, bool st = true);
	virtual ~GaussianParticleGenerator();

	// M�todo abstracto
	virtual list<Particle*> generateParticles();
};

