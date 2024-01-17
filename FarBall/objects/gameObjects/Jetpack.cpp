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
	setVelocity(Vector3(CONSTANT_X_VEL, 40, 0));
	isLaunched = true;
}

void Jetpack::useFuel() {
	fuel - 5 < 0 ? fuel = 0 : fuel -= 5;
}

void Jetpack::setFuel(int x) {
	x > 100 ? fuel = 100 : fuel = x;
}