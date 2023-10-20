#pragma once

#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
private:
	normal_distribution<float>* vX;
	normal_distribution<float>* vY;
	normal_distribution<float>* vZ;
	default_random_engine gen;


public:
	GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, Particle* m);
	//~GaussianParticleGenerator() {};

	virtual list<Particle*> generateParticles();
};

