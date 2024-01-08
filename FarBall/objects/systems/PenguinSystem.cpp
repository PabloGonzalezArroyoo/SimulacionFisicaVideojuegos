#include "PenguinSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../../RenderUtils.hpp"

void PenguinSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			break;
	}
}

void PenguinSystem::initSystem() {
	penguin = new Penguin(mngr->getPhysics(), mngr->getScene(), PxTransform(Vector3(0)),
		CreateShape(PxBoxGeometry(5, 5, 5)), NONE, Vector4(1, 1, 1, 1), 10);
	penguin->getDynRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	camera = GetCamera();
}

void PenguinSystem::update(double t) {
	// Actualizar posición
	penguin->integrate(t);
	Message m;
	m.id = _m_PENGUIN_POS_UPDATE;
	m.penguin_pos_data.x = penguin->getPos().x;
	m.penguin_pos_data.z = penguin->getPos().z;
	mngr->send(m);

	// Actualizar cámara
	camera->setView(penguin->getPos() + Vector3(0, 100, -200), Vector3(0.25f, -0.4f, 1.0f));
}

void PenguinSystem::keyPressed(char key) {

	switch (key) {
		case 'I':
			penguin->addForce(Vector3(100, 0, 0));
			break;
		case 'K':
			penguin->addForce(Vector3(-100, 0, 0));
			break;
		default: break;
	}
		
}