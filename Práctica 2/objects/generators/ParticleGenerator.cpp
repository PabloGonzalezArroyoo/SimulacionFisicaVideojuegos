#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob) :
	iniPos(iniPos), meanVel(medSpeed), meanVar(medVar), probability(prob) {
	srand((unsigned)time);

	cout << "Particle generation set with " << prob << " probability\n";
	cout << "Speed: (" << medSpeed.x << ", " << medSpeed.y << ", " << medSpeed.z << ")\n";
	cout << "Var:   (" << medVar.x << ", " << medVar.y << ", " << medVar.z << ")\n";
}

ParticleGenerator::~ParticleGenerator() {
	// delete model;
}

void ParticleGenerator::setParticle(Particle* m) {
	model = m;
}