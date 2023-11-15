#pragma once

#include "ForceGenerator.h"
#include "../../core.hpp"

class WindForceGenerator : public ForceGenerator {
protected:
	// k1 -> velocidad, k2 -> velocidad cuadrática
	float k1, k2;

public:
	WindForceGenerator();
	WindForceGenerator(const float _k1, const float _k2);

	virtual void updateForce(Particle* particle);

	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
};