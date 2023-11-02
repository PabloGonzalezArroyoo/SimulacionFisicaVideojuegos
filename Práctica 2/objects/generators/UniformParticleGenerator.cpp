#include "UniformParticleGenerator.h"

// Constructora - Setea la part�cula modelo y las distribuciones seg�n proceda
UniformParticleGenerator::UniformParticleGenerator(string n, Particle* m, Vector3 iniPos, Vector3 var, float f, bool st, Vector3 stOffset)
	: ParticleGenerator(n, m, iniPos, var, f, st, stOffset) {
	
	// Part�cula modelo
	m->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new uniform_real_distribution<float>(m->getVelocity().x - var.x, m->getVelocity().x + var.x);
	vY = new uniform_real_distribution<float>(m->getVelocity().y - var.y, m->getVelocity().y + var.y);
	vZ = new uniform_real_distribution<float>(m->getVelocity().z - var.z, m->getVelocity().z + var.z);

	// Distribuciones de posici�n
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

// Genera part�culas que se devuelven en la lista
list<Particle*> UniformParticleGenerator::generateParticles(double t) {
	// Lista de part�culas
	list<Particle*> prtcls;

	// Generar seg�n un aleatorio
	cont += t;
	if (cont > frecuency) {
		// Variables aleatorias
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = rand() % 10 + 3;

		// Crear part�cula
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