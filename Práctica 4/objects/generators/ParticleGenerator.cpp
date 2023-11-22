#include "ParticleGenerator.h"

// Constructora - Inicializa valores básicos, aleatorios y muestra información por pantalla
ParticleGenerator::ParticleGenerator(string n, Particle* p, Vector3 pos, Vector3 var, float f, bool st, Vector3 stOffset) : name(n),
	iniPos(pos), model(p), meanVel(p->getVelocity()), frecuency(f), cont(0), meanVar(var), staticGenerator(st), staticOffset(stOffset),
	gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count())) {
	srand((unsigned)time);
	p->setInvisible();
}

// Destructora
ParticleGenerator::~ParticleGenerator() {
	
}

void ParticleGenerator::setParticle(Particle* m, bool mod) {
	delete model;
	model = m->clone();
	if (mod) meanVel = m->getPos();
}