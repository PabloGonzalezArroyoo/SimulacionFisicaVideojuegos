#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 p, float r, float _k, float _tau) : ForceGenerator(Vector3(0)), radius(r),
	k(_k), tau(1 / _tau) { }

void ExplosionForceGenerator::updateForce(Particle* particle) {
	if (active && fabs(particle->getInvMass()) > 1e-10) {
		Vector3 pPos = particle->getPos();
		float r = (pPos - pos).magnitude();
		
		if (insideLimit(r)) {
			Vector3 force = k / powf(r, 2) * Vector3(pPos.x - pos.x, pPos.y - pos.y, pPos.z - pos.z) * exp(-t / tau);
			particle->addForce(force);
		}
	}
}

bool ExplosionForceGenerator::insideLimit(float r) {
	return r < radius;
}