#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator() {
	srand((unsigned)time);
}

ParticleGenerator::~ParticleGenerator() {

}

void ParticleGenerator::setParticle(Particle* model) {

}

list<Particle*> ParticleGenerator::generateParticles() {
	list<Particle*> prtcls;

	if (rand() % 10000 < 3) {

		// REVISAR ESTO
		float mediaX = 10, varianzaX = 5;
		float mediaY = 10, varianzaY = 5;
		float mediaZ = 10, varianzaZ = 5;
		float gaussX = powf(1 / (varianzaX * sqrt(2 * M_PI) * M_E), -(powf(10 - mediaX, 2) / powf(2 * varianzaX, 2)));
		float gaussY = powf(1 / (varianzaY * sqrt(2 * M_PI) * M_E), -(powf(10 - mediaY, 2) / powf(2 * varianzaY, 2)));
		float gaussZ = powf(1 / (varianzaZ * sqrt(2 * M_PI) * M_E), -(powf(10 - mediaZ, 2) / powf(2 * varianzaZ, 2)));

		Vector3 iniPos = Vector3(0, 0, 0);
		Vector3 vel = Vector3(0, 20, 0);
		Vector3 acc = Vector3(0, -10.0, 0);
		int lifeTime = rand() % 10 + 3;

		prtcls.push_back(new Particle(iniPos, vel, acc, lifeTime));
	}

	return prtcls;
}