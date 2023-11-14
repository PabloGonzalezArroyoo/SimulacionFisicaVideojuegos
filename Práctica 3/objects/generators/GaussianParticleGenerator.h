#pragma once

#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
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
	GaussianParticleGenerator(string n, Particle* m, Vector3 iniPos, Vector3 var = Vector3(0), float f = 0, bool st = true, Vector3 stOffset = Vector3(0));
	virtual ~GaussianParticleGenerator();

	// Método abstracto
	virtual list<Particle*> generateParticles(double t);
};

