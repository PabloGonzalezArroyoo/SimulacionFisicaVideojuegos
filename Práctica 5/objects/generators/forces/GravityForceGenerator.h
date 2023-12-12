#pragma once

#include "ForceGenerator.h"
#include "../../core.hpp"

class GravityForceGenerator : public ForceGenerator {
protected:
	Vector3 gravity;

public:
	GravityForceGenerator(const Vector3& g);

	virtual void updateForce(Particle* particle);

	inline void setGravity(Vector3 g) { gravity = g; }
};