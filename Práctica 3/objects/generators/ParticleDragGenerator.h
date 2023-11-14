#pragma once

#include "ForceGenerator.h"
#include "../../core.hpp"

class ParticleDragGenerator : public ForceGenerator {
protected:
	// k1 -> velocidad, k2 -> velocidad cuadrática
	float k1, k2;

public:
	ParticleDragGenerator();
	ParticleDragGenerator(const float k1, const float k2);

	virtual void updateForce(Particle* particle, double t);

	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
};