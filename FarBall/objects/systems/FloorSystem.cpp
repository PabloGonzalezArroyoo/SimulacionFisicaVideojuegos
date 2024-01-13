#include "FloorSystem.h"
#include "../../structure/ecs/Manager.h"

void FloorSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			break;
	}
}

void FloorSystem::initSystem() {
	floor = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(Vector3(0, -50, 0)),
		CreateShape(PxBoxGeometry(300, 2, 200)), NONE, Vector4(255, 255, 255, 1), 1000);
	floor->disableGravity();
	floor->getDynRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | 
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);
	mngr->addActor(_grp_GENERAL, floor);
}

void FloorSystem::update(double t) {
	Vector3 floorPos = floor->getPos();
	Vector3 penguinPos = mngr->getHandler(_hdlr_PENGUIN)->getPos();
	floor->setPos(Vector3(penguinPos.x + 100, floorPos.y, penguinPos.z));
}