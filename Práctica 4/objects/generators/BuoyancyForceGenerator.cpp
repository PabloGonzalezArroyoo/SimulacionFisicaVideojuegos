#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(Vector3 pos, float h, float v, float d) : ForceGenerator(pos), height(h), volume(v),
	liquidDensity(d) {
	liquidParticle = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(h, h, h)));
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete liquidParticle;
}

void BuoyancyForceGenerator::updateForce(Particle* particle) {
	float h = particle->getPos().y;
	float h0 = liquidParticle->getPos().y;

	float inmersed = 0.0;
	if (h - h0 > height * 0.5) inmersed = 0.0;
	else if (h0 - h > height * 0.5) inmersed = 1.0;
	else inmersed = (h0 - h) / height + 0.5;

	Vector3 force = Vector3(0, liquidDensity * volume * inmersed * gravity, 0);
	particle->addForce(force);
}