#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../core.hpp"
#include "../RenderUtils.hpp"

using namespace physx;

class Particle {
public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();

	void integrate(double t);

private:
	Vector3 vel;
	PxTransform pose;
	RenderItem* renderItem;
};