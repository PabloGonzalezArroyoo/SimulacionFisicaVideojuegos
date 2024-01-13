#include "Penguin.h"

Penguin::Penguin(PxPhysics* ph, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m) :
	RigidBody(ph, sc, t, s, st, c, m) {

}

void Penguin::keyPressed(char key) {
	switch (key) {
		case 'I':
			addForce(Vector3(0, 100, 0));
			break;
		case 'K':
			addForce(Vector3(0, -100, 0));
			break;
		default: break;
	}
}