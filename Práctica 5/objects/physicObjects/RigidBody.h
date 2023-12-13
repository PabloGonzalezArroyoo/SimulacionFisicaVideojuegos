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

	// Clonar
	RigidBody* clone() const;

	// Getters y setters
	inline Vector3 getVelocity() { return dnRigid != nullptr ? dnRigid->getLinearVelocity() : Vector3(0); }
};

