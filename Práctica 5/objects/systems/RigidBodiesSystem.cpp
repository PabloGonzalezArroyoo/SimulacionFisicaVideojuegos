#include "RigidBodiesSystem.h"

RigidBodiesSystem::RigidBodiesSystem(PxPhysics* gPhysics, PxScene* gScene) {
	RigidBody* floor = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(-20)),
		CreateShape(PxBoxGeometry(400, 2, 400)), rColors[R_BLUE], false);
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), rColors[R_YELLOW]);
}

RigidBodiesSystem::~RigidBodiesSystem() {

}

void RigidBodiesSystem::update(double t) {

}

void RigidBodiesSystem::keyPress(char t) {

}