#pragma once

#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator {
protected:
	double k, resisting_length;
	Particle* other;

public:
	SpringForceGenerator(Vector3 pos, double _k, double rl, Particle* oth);
	//virtual ~SpringForceGenerator();

	virtual void updateForce(Particle* particle);

	inline void setK(double _k) { k = _k; }

};

