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
	PxShape* shape;
	Vector4 color;

	// Properties
	Vector3 vel, accl, gravity;
	PxTransform pos;
	float mass, damping;

	// Tiempo
	float startTime, lifeTime;

public:
	// Constructoras y destructora
	Particle(float m, Vector3 p, Vector3 vel, Vector3 ac, int lTime, Vector4 col, PxShape* shp);
	Particle(float m, Vector3 vel, Vector3 ac, Vector4 col, PxShape* shp);
	~Particle();

	// Actualizar
	bool integrate(double t);

	// Clonar partícula
	virtual Particle* clone(Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime) const;
	virtual Particle* clone(Vector3 newPos, Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime) const;

	// Getters y setters
	void setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float l, float d = 0.998);
	#pragma region getters&setters
	inline void setMass(float m) { mass = m; }
	inline void setVelocity(Vector3 v) { vel = v; }
	inline void setAcceleration(Vector3 a) { accl = a; }
	inline void setDamping(float d) { damping = d; }
	inline void setColor(Vector4 c) { color = c; }
	inline void setShape(PxShape* s) { shape = s; }
	inline void setLifeTime(float l) { lifeTime = l; }
	inline void setPos(Vector3 p) { pos.p = p; }

	inline float getMass() { return mass; }
	inline Vector3 getVelocity() { return vel; }
	inline Vector3 getAcceleration() { return accl; }
	// inline float getDamping() { return damping; }
	inline Vector4 getColor() { return color; }
	inline PxShape* getShape() { return shape; }
	inline float getLifeTime() { return lifeTime; }
	#pragma endregion
	
};