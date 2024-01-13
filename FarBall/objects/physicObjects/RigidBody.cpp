#include "RigidBody.h"

// Constructora
RigidBody::RigidBody(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* sp, ElimState st, Vector4 c, float m, bool d) : gPhysics(p),
	Actor(t, sp, st, c), gScene(sc), dynamic(d) {
	if (dynamic) {
		dnRigid = gPhysics->createRigidDynamic(tr);
		dnRigid->attachShape(*shape);
		gScene->addActor(*dnRigid);
		renderItem = new RenderItem(shape, dnRigid, color);
		dnRigid->setMass(m);
		PxRigidBodyExt::setMassAndUpdateInertia(*static_cast<PxRigidBody*>(dnRigid), getMass() / getVolume());
	}
	else {
		stRigid = gPhysics->createRigidStatic(tr);
		stRigid->attachShape(*shape);
		gScene->addActor(*stRigid);
		renderItem = new RenderItem(shape, stRigid, color);
	}
}

RigidBody::~RigidBody() {
	if (dnRigid != nullptr) dnRigid->release();
	if (stRigid != nullptr) stRigid->release();
	renderItem->release();
	renderItem = nullptr;
}

// Update
void RigidBody::integrate(double t) {
	// Actualizar posición
	Vector3 vel = getVelocity();
	vel *= powf(damping, t);
	tr.p += vel * t;

	// Borrar fuerza 
	//clearForce();

	// Eliminar tras lifeTime segundos
	if (state == TIME && (startTime + lifeTime < GetLastTime())) setAlive(false);
	// Eliminar si ha sobrepasado el límite
	else if (state == BOUNDARIES && !insideLimit()) setAlive(false);
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	else if (state == BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) setAlive(false);
}

// Clona la partícula actual
RigidBody* RigidBody::clone() const {
	RigidBody* rb = new RigidBody(gPhysics, gScene, tr, shape, state, color, dynamic);
	rb->setLifeTime(lifeTime);
	rb->setBoundaries(limits);
	return rb;
}

// Clona la partícula actual
RigidBody* RigidBody::clone(PxTransform t, Vector3 v) const {
	RigidBody* rb = new RigidBody(gPhysics, gScene, t, shape, state, color, dynamic);
	rb->setVelocity(v);
	rb->setLifeTime(lifeTime);
	rb->setBoundaries(limits);
	return rb;
}