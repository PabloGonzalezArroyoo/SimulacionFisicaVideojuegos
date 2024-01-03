#pragma once

#include "Actor.h"

class Particle : public Actor {
protected:
	// Properties
	Vector3 vel, accl, force;
	float mass, invMass;	

public:
	// Constructoras y destructora
	Particle(Vector3 p, Vector3 vel, ElimState st, Vector4 col, PxShape* shp, float m = 10);
	virtual ~Particle();

	// Actualizar
	virtual bool integrate(double t);
	void reset();

	// Clonar partícula
	virtual Particle* clone() const;
	Particle* clone(ElimState mode, Vector3 newRanVel, Vector3 newPos, float newLifeTime = 0) const;
	virtual Particle* clone(PxTransform t, Vector3 v = Vector3(0)) const;

	// Fuerzas
	virtual inline void clearForce() { force *= 0.0; }
	virtual inline void addForce(const Vector3& f) { force += f; }

	#pragma region getters&setters
	inline void setMass(float m) { mass = m; invMass = 1 / m; }
	inline void setVelocity(Vector3 v) { vel = v; }
	virtual float getMass() { return mass; }
	inline float getInvMass() { return invMass; }
	virtual Vector3 getVelocity() { return vel; }
	#pragma endregion
};