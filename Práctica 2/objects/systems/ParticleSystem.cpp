#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::update(double t) {
	for (Particle* p : _particles) {
		if (!p->integrate(t)) {
			Particle* deletedParticle = *_particles.begin();
			_particles.erase(_particles.begin());
			delete deletedParticle;
		}
	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name) {

}

void ParticleSystem::generateFireworkSystem() {

}