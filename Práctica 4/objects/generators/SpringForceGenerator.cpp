#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(Vector3 pos, double _k, double rl, Particle* oth, bool el) : ForceGenerator(pos), k(_k),
	resisting_length(rl), other(oth), elastic(el) {
	//other = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(1, 1, 1)));
}

void SpringForceGenerator::updateForce(Particle* particle) {
	// particle -> particula a la que se le añade la fuerza
	if (active) {
		Vector3 relativePosVector = other->getPos() - particle->getPos();
		if (elastic && relativePosVector.magnitude() < resisting_length)
			return;

		double length = relativePosVector.normalize();
		float deltaX = length - resisting_length;

		Vector3 force = relativePosVector * deltaX * k;
		particle->addForce(force);
	}
}