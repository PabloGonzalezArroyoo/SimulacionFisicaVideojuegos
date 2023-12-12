#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../../core.hpp"
#include "../../RenderUtils.hpp"

using namespace physx;

enum RigidColor { R_RED, R_BLUE, R_YELLOW, R_GREEN };
enum RElimState { R_TIME, R_BOUNDARIES, R_BOTH, R_NONE };

const std::vector<Vector4> rColors = {
	Vector4(125, 0, 0, 1),
	Vector4(0, 125, 125, 1),
	Vector4(125, 125, 0, 1),
	Vector4(0, 125, 0, 1)
};

class RigidBody {
private:
	PxTransform* tr;
	PxShape* shape;
	Vector4 color;

	PxPhysics* gPhysics;
	PxScene* gScene;
	RenderItem* renderItem;

	bool dynamic;
	PxRigidDynamic* dnRigid;
	PxRigidStatic* stRigid;

	Vector3 iniPos;

	// Modo
	RElimState state;
	// Tiempo
	float startTime, lifeTime;
	// Barrera
	Vector3 limits;

public:
	// Constructora y destructora
	RigidBody(PxPhysics* p, PxScene* sc, PxTransform* t, PxShape* s, RElimState st, Vector4 c, bool d = true);
	~RigidBody();

	// Actualizar
	bool integrate(double t);
	bool insideLimit();

	// Clonar
	RigidBody* clone() const;

	// Getters y setters
	inline Vector3 getPos() { return tr->p; }
	inline Vector3 getVelocity() { return dnRigid != nullptr ? dnRigid->getLinearVelocity() : Vector3(0); }
	inline RElimState getState() { return state; }
	inline void setPos(Vector3 p) { tr->p = p; }
	inline void setLifeTime(float l) { lifeTime = l; }
	inline void setBoundaries(Vector3 lmt) { limits = lmt; }
};

