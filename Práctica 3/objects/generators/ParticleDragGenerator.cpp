
#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	if (fabs(particle->getInvMass()) > 1e-10) {
		Vector3 v = particle->getVelocity();
		float dragCoef = v.normalize();
		Vector3 dragF;
		dragCoef = k1 * dragCoef + k2 * dragCoef * dragCoef;
		dragF = -v * dragCoef;

		cout << dragF.x << " " << dragF.y << " " << dragF.z << endl;
		particle->addFroce(dragF);
	}
}