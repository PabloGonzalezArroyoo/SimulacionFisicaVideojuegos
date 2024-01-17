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
	// Crear suelo y restringir movimiento
	floor = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(Vector3(0, -50, 0)),
		CreateShape(PxBoxGeometry(300, 2, 200)), NONE, Vector4(255, 255, 255, 1), 1000);
	floor->disableGravity();
	floor->getDynRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Y |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | 
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// Crear sombra
	shadow = new Particle(Vector3(0, -47.75, 0), Vector3(0), NONE, Vector4(0.1, 0.1, 0.1, 1),
		CreateShape(PxBoxGeometry(10, 0.1, 15)));

	// Guardar referencia al jetpack
	jetpack = static_cast<Jetpack*>(mngr->getHandler(_hdlr_JETPACK));

	// Añadir al manager
	mngr->addActor(_grp_GENERAL, floor);
	mngr->addActor(_grp_GENERAL, shadow);
}

void FloorSystem::update(double t) {
	// Coger posición del pinguino
	Vector3 penguinPos = jetpack->getDynRigid()->getGlobalPose().p;

	// Actualizar posiciones del suelo y sombra
	Vector3 floorPos = floor->getPos();
	Vector3 shadowPos = shadow->getPos();
	floor->setPos(Vector3(penguinPos.x + 100, floorPos.y, floorPos.z));
	shadow->setPos(Vector3(penguinPos.x, shadowPos.y, shadowPos.z));
}