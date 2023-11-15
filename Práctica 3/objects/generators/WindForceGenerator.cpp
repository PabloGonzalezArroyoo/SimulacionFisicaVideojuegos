
#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const float _k1, const float _k2) : k1(_k1), k2(_k2){}

void WindForceGenerator::updateForce(Particle* particle) {
	if (fabs(particle->getInvMass()) > 1e-10) {
		Vector3 v = particle->getVelocity();
		float dragCoef = v.normalize();
		Vector3 dragF;
		dragCoef = k1 * dragCoef + k2 * dragCoef * dragCoef;
		dragF = -v * dragCoef;

		//cout << dragF.x << " " << dragF.y << " " << dragF.z << endl;
		particle->addFroce(dragF);
	}
}