#include "Penguin.h"

Penguin::Penguin(PxPhysics* ph, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m) :
	RigidBody(ph, sc, t, s, st, c, m), isLaunched(false) {

	//decorations = {
	//	// Ojos
	//	new Particle(t.p + Vector3(5, 2, -2), Vector3(0), NONE, Vector4(1, 1, 1, 1),
	//	CreateShape(PxBoxGeometry(1, 1, 1))),
	//	new Particle(t.p + Vector3(5, 2, 2), Vector3(0), NONE, Vector4(1, 1, 1, 1),
	//	CreateShape(PxBoxGeometry(1, 1, 1))),
	//	new Particle(t.p + Vector3(5.6, 2, -2), Vector3(0), NONE, Vector4(0, 0, 0, 1),
	//	CreateShape(PxBoxGeometry(0.5, 0.5, 0.5))),
	//	new Particle(t.p + Vector3(5.6, 2, 2), Vector3(0), NONE, Vector4(0, 0, 0, 1),
	//	CreateShape(PxBoxGeometry(0.5, 0.5, 0.5))),

	//	// Pies
	//	new Particle(t.p + Vector3(-5, -4, -3), Vector3(0), NONE, Vector4(0.7, 0.4, 0.2, 1),
	//	CreateShape(PxBoxGeometry(0.5, 3, 1.5))),
	//	new Particle(t.p + Vector3(-5, -4, 3), Vector3(0), NONE, Vector4(0.7, 0.4, 0.2, 1),
	//	CreateShape(PxBoxGeometry(0.5, 3, 1.5))),

	//	// Pico
	//	new Particle(t.p + Vector3(5, -3, 0), Vector3(0), NONE, Vector4(0.7, 0.4, 0.2, 1),
	//	CreateShape(PxBoxGeometry(2, 1, 1))),
	//};
}

void Penguin::integrate(double t) {
	RigidBody::integrate(t);
	if (isLaunched) setPos(getPos());
}

void Penguin::keyPressed(char key) {
	switch (key) {
		case ' ':
			addForce(Vector3(0, -100, 0));
			break;
		default: break;
	}
}

void Penguin::launch() {
	//clearForce();
	//addForce(Vector3(4000, 3200, 0));
	setVelocity(Vector3(200, 40, 0));
	
	isLaunched = true;
}