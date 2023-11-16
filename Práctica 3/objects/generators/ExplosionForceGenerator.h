#pragma once

#include "ForceGenerator.h"
#include <numbers>

class ExplosionForceGenerator : public ForceGenerator {
private:
	float radius, k, tau;

public:
	ExplosionForceGenerator(Vector3 p, float r, float _k, float _tau);

	virtual void updateForce(Particle* particle);

	bool insideLimit(float r);
};