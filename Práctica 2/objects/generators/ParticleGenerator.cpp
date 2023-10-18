#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 medSpeed, Vector3 medVar, int prob) : probability(prob), 
	gen(std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count())) {

}

ParticleGenerator::~ParticleGenerator() {

}

void ParticleGenerator::setParticle(Particle* model) {

}

list<Particle*> ParticleGenerator::generateParticles() {
	list<Particle*> prtcls;

	if (rand() % 10000 < probability) {

		// REVISAR ESTO
		std::normal_distribution<float>* vX = new std::normal_distribution<float>(50, 45);
		std::normal_distribution<float>* vY = new std::normal_distribution<float>(50, 45);
		std::normal_distribution<float>* vZ = new std::normal_distribution<float>(50, 45);
		
		Vector3 iniPos = Vector3(0, 0, 0);
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		Vector3 acc = Vector3(0, -10.0, 0);
		int lifeTime = rand() % 10 + 3;

		prtcls.push_back(new Particle(iniPos, vel, acc, lifeTime));
	}

	return prtcls;
}