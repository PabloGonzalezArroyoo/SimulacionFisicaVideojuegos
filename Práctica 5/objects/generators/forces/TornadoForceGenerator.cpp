#include "TornadoForceGenerator.h"

TornadoForceGenerator::TornadoForceGenerator(Vector3 p, float size, float _k) : WindForceGenerator(p, Vector3(0), size, Vector4(0, 0, 0, 1), 1),
	k(_k) { }

void TornadoForceGenerator::updateForce(Particle* particle) {
	if (active && fabs(particle->getInvMass()) > 1e-10 && insideLimit(particle->getPos())) {
		Vector3 pPos = particle->getPos();
		Vector3 vel = k * Vector3(pos.z - pPos.z, 50 - pPos.y + pos.y, pPos.x - pos.x);
		particle->addForce(vel);

		//WindForceGenerator::updateForce(particle);
	}
}

bool TornadoForceGenerator::insideLimit(Vector3 p) {
	return p.x < pos.x + size
		&& p.x > pos.x - size
		&& p.z < pos.z + size
		&& p.z > pos.z - size;
}