#include "GaussianParticleGenerator.h"

// Constructora - Setea la part�cula modelo y las distribuciones seg�n proceda
GaussianParticleGenerator::GaussianParticleGenerator(string n, Particle* m, Vector3 iniPos, Vector3 var, float f, bool st)
	: ParticleGenerator(n, m, iniPos, var, f,st) {

	// Part�cula modelo
	m->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new normal_distribution<float>(m->getVelocity().x, var.x);
	vY = new normal_distribution<float>(m->getVelocity().y, var.y);
	vZ = new normal_distribution<float>(m->getVelocity().z, var.z);

	// Distribuciones de posici�n
	if (!st) {
		pX = new normal_distribution<float>(iniPos.x, var.x / 2.0f);
		pY = new normal_distribution<float>(iniPos.y, var.y / 2.0f);
		pZ = new normal_distribution<float>(iniPos.z, var.z / 2.0f);
	}
}

// Destructora
GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
}

// Genera part�culas que se devuelven en la lista
list<Particle*> GaussianParticleGenerator::generateParticles(double t) {
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
		if (!staticGenerator) {
			Vector3 pos = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
			prtcls.push_back(model->clone(vel, lifeTime, pos));
		}
		else prtcls.push_back(model->clone(vel, lifeTime, model->getPos()));

		cont = 0;
	}

	return prtcls;
}