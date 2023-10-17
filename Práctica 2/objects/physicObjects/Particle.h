#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../../core.hpp"
#include "../../RenderUtils.hpp"
#include <iostream>

using namespace physx;

class Particle {
protected:
	// Render
	RenderItem* renderItem;

	// Properties
	Vector3 vel;
	PxTransform pose;
	Vector3 accl;
	float mass;

	// Variables
	float damping;
	float startTime;
	float lifeTime;

public:
	Particle() {};
	Particle(Vector3 pos, Vector3 vel, Vector3 ac, int lTime);
	~Particle();

	bool integrate(double t);

	void setProperties(float m, Vector3 v, Vector3 a, float d);
	inline void setMass(float m) { mass = m; }
	inline void setVelocity(Vector3 v) { vel = v; }
	inline void setAcceleration(Vector3 a) { accl = a; }
	inline void setDamping(float d) { damping = d; }
};