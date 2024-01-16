#include "Jetpack.h"

Jetpack::Jetpack(PxPhysics* ph, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m) :
	RigidBody(ph, sc, t, s, st, c, m), isLaunched(false) {

}

void Jetpack::integrate(double t) {
	RigidBody::integrate(t);
	if (isLaunched) {
		Vector3 pose = getPos();
		if (pose.y > 110) pose.y = 110;
		setPos(pose);
	}
}

void Jetpack::launch() {
	//clearForce();
	//addForce(Vector3(4000, 3200, 0));
	setVelocity(Vector3(200, 40, 0));
	
	isLaunched = true;
}