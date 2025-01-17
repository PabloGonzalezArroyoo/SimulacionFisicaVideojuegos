
#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(Vector3 p, Vector3 v, float s, Vector4 c, float _k1, bool txt,  float _k2) : ForceGenerator(pos),
vel(v), size(s), k1(_k1), k2(_k2) {
	name = "wind";
	pos = p;
	if (txt) new Particle(p, Vector3(0), BOUNDARIES, c, CreateShape(PxBoxGeometry(s, 1, s)));
}

void WindForceGenerator::updateForce(Particle* particle) {
	if (active && fabs(particle->getInvMass()) > 1e-10 && insideLimit(particle->getPos())) {
		Vector3 diffVel = vel - particle->getVelocity();
		Vector3 dragF = k1 * diffVel + k2 * diffVel.magnitude() * diffVel;
		particle->addForce(dragF);
	}
}

bool WindForceGenerator::insideLimit(Vector3 p) {
	return p.x < pos.x + size
		&& p.x > pos.x - size
		&& p.y < pos.y + size * 2
		&& p.y > pos.y - size
		&& p.z < pos.z + size
		&& p.z > pos.z - size;
}