#include "RigidBody.h"

// Constructora
RigidBody::RigidBody(PxPhysics* p, PxScene* sc, PxTransform* t, PxShape* sp, Vector4 c, bool d) : gPhysics(p), gScene(sc),
	tr(t), shape(sp), dynamic(d) {
	if (dynamic) {
		dnRigid = gPhysics->createRigidDynamic(*tr);
		dnRigid->attachShape(*shape);
		gScene->addActor(*dnRigid);
		renderItem = new RenderItem(shape, dnRigid, c);
	}
	else {
		stRigid = gPhysics->createRigidStatic(*tr);
		stRigid->attachShape(*shape);
		gScene->addActor(*stRigid);
		renderItem = new RenderItem(shape, stRigid, c);
	}
}

// Destructora
RigidBody::~RigidBody() {
	renderItem->release();
	renderItem = nullptr;
};