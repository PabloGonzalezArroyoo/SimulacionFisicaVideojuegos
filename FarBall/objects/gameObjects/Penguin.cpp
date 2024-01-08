#include "Penguin.h"

Penguin::Penguin(PxPhysics* ph, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m) :
	RigidBody(ph, sc, t, s, st, c, m) {

}