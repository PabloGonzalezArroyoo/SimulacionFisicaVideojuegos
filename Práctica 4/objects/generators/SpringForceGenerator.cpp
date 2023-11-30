#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Vector3 pos, double _k, double rl, Particle* oth, bool el) : ForceGenerator(pos), k(_k),
	resisting_length(rl), other(oth), elastic(false) {}

void SpringForceGenerator::updateForce(Particle* particle) {
	// particle -> particula a la que se le añade la fuerza
	if (active) {
		Vector3 relativePosVector = other->getPos() - particle->getPos();
		double length = relativePosVector.normalize();
		float deltaX = length - resisting_length;

		Vector3 force = relativePosVector * deltaX * k;
		particle->addForce(force);
	}
}