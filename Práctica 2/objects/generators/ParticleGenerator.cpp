#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator() {
	srand((unsigned)time);


}

ParticleGenerator::~ParticleGenerator() {

}

void ParticleGenerator::setParticle(Particle* model) {

}

list<Particle*> ParticleGenerator::generateParticles() {
	int n = rand() % 10;
	if (n < 3) {
		
	}
}