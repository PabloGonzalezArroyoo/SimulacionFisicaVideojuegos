#pragma once

#include "WindForceGenerator.h"

class TornadoForceGenerator : public WindForceGenerator {
private:
	float k;

public:
	TornadoForceGenerator(Vector3 p, float size, float k);

	virtual void updateForce(Particle* particle);

	virtual bool insideLimit(Vector3 p);
};

