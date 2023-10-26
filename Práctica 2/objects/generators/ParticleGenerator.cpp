#include "ParticleGenerator.h"

// Constructora - Inicializa valores básicos, aleatorios y muestra información por pantalla
ParticleGenerator::ParticleGenerator(string n, Particle* p, Vector3 pos, Vector3 var, float f, bool st) : name(n),
	iniPos(pos), frecuency(f), cont(0), staticGenerator(st), model(p), meanVel(p->getVelocity()), meanVar(var),
	gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
	srand((unsigned)time);
}

// Destructora
ParticleGenerator::~ParticleGenerator() {
	delete model;
}

void ParticleGenerator::setParticle(Particle* m, bool mod) {
	delete model;
	model = m->clone();
	if (mod) meanVel = m->getPos();
}