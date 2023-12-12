#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : ForceGenerator(Vector3(0)), gravity(g) {
	name = "gravity";
}

void GravityForceGenerator::updateForce(Particle* p) {
	if (active && fabs(p->getInvMass()) > 1e-10)
		p->addForce(gravity * p->getMass());
}