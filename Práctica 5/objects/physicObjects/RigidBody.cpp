#include "RigidBody.h"

// Constructora
RigidBody::RigidBody(PxPhysics* p, PxScene* sc, PxTransform* t, PxShape* sp, ElimState st, Vector4 c, bool d) : gPhysics(p),
	Actor(t, sp, st, c), gScene(sc), dynamic(d) {
	if (dynamic) {
		dnRigid = gPhysics->createRigidDynamic(*tr);
		dnRigid->attachShape(*shape);
		gScene->addActor(*dnRigid);
		renderItem = new RenderItem(shape, dnRigid, color);
	}
	else {
		stRigid = gPhysics->createRigidStatic(*tr);
		stRigid->attachShape(*shape);
		gScene->addActor(*stRigid);
		renderItem = new RenderItem(shape, stRigid, color);
	}
}

RigidBody::~RigidBody() {
	if (dnRigid != nullptr) dnRigid->release();
	if (stRigid != nullptr) stRigid->release();
}

// Update
bool RigidBody::integrate(double t) {

	// Eliminar tras lifeTime segundos
	if (state == TIME && (startTime + lifeTime < GetLastTime())) return false;
	// Eliminar si ha sobrepasado el límite
	else if (state == BOUNDARIES && !insideLimit()) return false;
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	else if (state == BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) return false;

	return true;
}

// Clona la partícula actual
RigidBody* RigidBody::clone() const {
	RigidBody* rb = new RigidBody(gPhysics, gScene, tr, shape, state, color, dynamic);
	rb->setLifeTime(lifeTime);
	rb->setBoundaries(limits);
	return rb;
}