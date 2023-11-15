#pragma once

#include "ForceGenerator.h"
#include "../../core.hpp"

class WindForceGenerator : public ForceGenerator {
protected:
	// k1 -> velocidad, k2 -> velocidad cuadrática
	float k1, k2;
	Vector3 vel, pos;
	float size;

public:
	WindForceGenerator();
	WindForceGenerator(Vector3 p, Vector3 v, float s, const float _k1, const float _k2 = 0);

	virtual void updateForce(Particle* particle);
	bool insideLimit(Vector3 p);

	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
};