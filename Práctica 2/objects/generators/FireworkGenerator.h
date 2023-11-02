#pragma once

#include "ParticleGenerator.h"
#include "UniformParticleGenerator.h"

class FireworkGenerator : public UniformParticleGenerator {
private:
	bool initiateGenerator;

public:
	FireworkGenerator(string n, Particle* p, Vector3 pos, Vector3 var);
	virtual ~FireworkGenerator();

	virtual list<Particle*> generateParticles(double t);

	void resetGenerator() { initiateGenerator = true; }
	void recalculateDistributions(Vector3 vel);
	Vector3 obtainDistributionVelValues();
};