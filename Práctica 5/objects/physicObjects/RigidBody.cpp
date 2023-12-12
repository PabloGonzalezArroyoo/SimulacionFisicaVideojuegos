#include "RigidBody.h"

// Constructora
RigidBody::RigidBody(PxPhysics* p, PxScene* sc, PxTransform* t, PxShape* sp, RElimState st, Vector4 c, bool d) : gPhysics(p),
	gScene(sc), tr(t), shape(sp), state(st), color(c), dynamic(d), iniPos(tr->p) {
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

// Destructora
RigidBody::~RigidBody() {
	renderItem->release();
	renderItem = nullptr;
};

// Update
bool RigidBody::integrate(double t) {

	// Eliminar tras lifeTime segundos
	if (state == R_TIME && (startTime + lifeTime < GetLastTime())) return false;
	// Eliminar si ha sobrepasado el límite
	else if (state == R_BOUNDARIES && !insideLimit()) return false;
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	else if (state == R_BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) return false;

	return true;
}

// Comprueba si está dentro de los límites
bool RigidBody::insideLimit() {
	return tr->p.y < limits.y + iniPos.y
		&& tr->p.y > -limits.y + iniPos.y
		&& tr->p.x < limits.x + iniPos.x
		&& tr->p.x > -limits.x + iniPos.x
		&& tr->p.z < limits.z + iniPos.z
		&& tr->p.z > -limits.z + iniPos.z;
}

// Clona la partícula actual
RigidBody* RigidBody::clone() const {
	RigidBody* rb = new RigidBody(gPhysics, gScene, tr, shape, state, color, dynamic);
	rb->setLifeTime(lifeTime);
	rb->setBoundaries(limits);
	return rb;
}