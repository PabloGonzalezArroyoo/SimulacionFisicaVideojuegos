#pragma once

#include "../physicObjects/Particle.h"
#include "UniformGenerator.h"

class FireworkGenerator : public UniformGenerator {
private:
	bool initiateGenerator;
	Vector3 iniPos;

public:
	FireworkGenerator(string n, Particle* p, Vector3 pos, Vector3 var);
	virtual ~FireworkGenerator();

	virtual list<Actor*> generateParticles(double t);

	void resetGenerator() { initiateGenerator = true; }
	void recalculateDistributions(Vector3 vel);
	Vector3 obtainDistributionVelValues();
};