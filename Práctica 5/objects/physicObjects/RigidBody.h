#pragma once

#include "Actor.h"

class RigidBody : public Actor {
private:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	// Sólidos
	bool dynamic;
	PxRigidDynamic* dnRigid = nullptr;
	PxRigidStatic* stRigid = nullptr;

public:
	// Constructora y destructora
	RigidBody(PxPhysics* p, PxScene* sc, PxTransform* t, PxShape* s, ElimState st, Vector4 c, bool d = true);
	~RigidBody();

	// Actualizar
	bool integrate(double t);
	virtual void addForce(const Vector3& f) { 
		if (dnRigid != nullptr) dnRigid->addForce(f); }
	virtual void clearForce() { if (dnRigid != nullptr) dnRigid->clearForce(); }

	// Clonar
	RigidBody* clone() const;
	RigidBody* clone(PxTransform* t, Vector3 v = Vector3(0)) const;

	// Getters y setters
	virtual float getMass() { return dnRigid != nullptr ? dnRigid->getMass() : 1e-10; };
	inline Vector3 getVelocity() { return dnRigid != nullptr ? dnRigid->getLinearVelocity() : Vector3(0); }
	inline void setVelocity(Vector3 v) { if (dnRigid != nullptr) dnRigid->setLinearVelocity(Vector3(v)); }
	virtual void setMass(float m) { if (dnRigid != nullptr) dnRigid->setMass(m); }
};

