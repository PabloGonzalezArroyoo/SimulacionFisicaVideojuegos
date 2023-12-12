#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../../core.hpp"
#include "../../RenderUtils.hpp"

using namespace physx;

enum RigidColor { R_RED, R_BLUE, R_YELLOW, R_GREEN };

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
	PxPhysics* gPhysics;
	PxScene* gScene;
	RenderItem* renderItem;

	bool dynamic;
	PxRigidDynamic* dnRigid;
	PxRigidStatic* stRigid;

public:
	RigidBody(PxPhysics* p, PxScene* g, PxTransform* t, PxShape* s, Vector4 c, bool d = true);
	~RigidBody();
};

