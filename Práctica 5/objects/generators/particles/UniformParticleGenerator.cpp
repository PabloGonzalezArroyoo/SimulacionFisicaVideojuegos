#include "UniformParticleGenerator.h"

// Constructora - Setea la partícula modelo y las distribuciones según proceda
UniformParticleGenerator::UniformParticleGenerator(string n, Particle* m, Vector3 iniPos, Vector3 var, float f, bool st, Vector3 stOffset)
	: ParticleGenerator(n, m, iniPos, var, f, st, stOffset) {
	
	// Partícula modelo
	m->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new uniform_real_distribution<float>(m->getVelocity().x - var.x, m->getVelocity().x + var.x);
	vY = new uniform_real_distribution<float>(m->getVelocity().y - var.y, m->getVelocity().y + var.y);
	vZ = new uniform_real_distribution<float>(m->getVelocity().z - var.z, m->getVelocity().z + var.z);

	// Distribuciones de posición
	if (!st) {
		pX = new uniform_real_distribution<float>(iniPos.x - stOffset.x, iniPos.x + stOffset.x);
		pY = new uniform_real_distribution<float>(iniPos.y - stOffset.y, iniPos.y + stOffset.y);
		pZ = new uniform_real_distribution<float>(iniPos.z - stOffset.z, iniPos.z + stOffset.z);
	}
}

// Destructora
UniformParticleGenerator::~UniformParticleGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

// Genera partículas que se devuelven en la lista
list<Particle*> UniformParticleGenerator::generateParticles(double t) {
	// Lista de partículas
	list<Particle*> prtcls;

	// Generar según un aleatorio
	cont += t;
	if (cont > frecuency) {
		// Variables aleatorias
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = rand() % 10 + 3;

		// Crear partícula
		ElimState st = model->getState();
		if (!staticGenerator) {
			Vector3 pos = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
			if (st == BOUNDARIES) prtcls.push_back(model->clone(st, vel, pos));
			else prtcls.push_back(model->clone(st, vel, pos, lifeTime));
		}
		else {
			if (st == BOUNDARIES) prtcls.push_back(model->clone(st, vel, model->getPos()));
			else prtcls.push_back(model->clone(st, vel, model->getPos(), lifeTime));
		}

		cont = 0;
	}

	return prtcls;
}