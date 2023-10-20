#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 iniPos, Vector3 var, float prob, Particle* m)
	: ParticleGenerator(iniPos, m->getVelocity(), var, prob),
	gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
	srand((unsigned)time);
	
	m->setPos(iniPos);
	setParticle(m);

	vX = new normal_distribution<float>(m->getVelocity().x, var.x);
	vY = new normal_distribution<float>(m->getVelocity().y, var.y);
	vZ = new normal_distribution<float>(m->getVelocity().z, var.z);
}

list<Particle*> GaussianParticleGenerator::generateParticles() {
	list<Particle*> prtcls;

	float random = (rand() % 101) / 100.0f;
	if (random < probability) {
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = rand() % 10 + 3;

		prtcls.push_back(model->clone(vel, accl, lifeTime));
	}

	return prtcls;
}