#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : gravity(g) {}

void GravityForceGenerator::updateForce(Particle* p) {
	if (fabs(p->getInvMass()) > 1e-10) 
		p->addFroce(gravity * p->getMass());
}