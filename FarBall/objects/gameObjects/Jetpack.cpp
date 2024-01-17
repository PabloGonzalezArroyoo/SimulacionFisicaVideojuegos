#include "Jetpack.h"

Jetpack::Jetpack(PxPhysics* ph, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m) :
	RigidBody(ph, sc, t, s, st, c, m), isLaunched(false) {

}

// Actualizar
void Jetpack::integrate(double t) {
	RigidBody::integrate(t);

	// Si está en el aire
	if (isLaunched) {
		// Límites de posición
		Vector3 pose = getPos();
		if (pose.y > 110) pose.y = 110;
		setPos(pose);

		// Límites de velocidad
		Vector3 velocity = getVelocity();
		if (velocity.y > 40) setVelocity(Vector3(velocity.x, 40, velocity.z));
		else if (velocity.y < -40) setVelocity(Vector3(velocity.x, -40, velocity.z));
	}
}

// Lanzar el jetpack y marcar como lanzado
void Jetpack::launch() {
	setVelocity(Vector3(CONSTANT_X_VEL, 40, 0));
	isLaunched = true;
}

// Restar combustible
void Jetpack::useFuel() {
	fuel - 5 < 0 ? fuel = 0 : fuel -= 5;
}

// Repostar combustible
void Jetpack::setFuel(int x) {
	x > 100 ? fuel = 100 : fuel = x;
}