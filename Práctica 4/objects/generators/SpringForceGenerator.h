#pragma once

#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator {
protected:
	double k, resisting_length;
	Particle* other;
	bool elastic;

public:
	SpringForceGenerator(Vector3 pos, double _k, double rl, Particle* oth, bool el = false);

	virtual void updateForce(Particle* particle);

	inline void setK(double _k) { k = _k; }
	inline double getK() { return k; }
};

