#include "UniformGenerator.h"

// Constructora - Setea la part�cula modelo y las distribuciones seg�n proceda
UniformGenerator::UniformGenerator(string n, Actor* rb, Vector3 iniPos, Vector3 var, float f, bool st,
	Vector3 stOffset) : ActorGenerator(n, rb, iniPos, var, f, st, stOffset) {

	// Part�cula modelo
	rb->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new uniform_real_distribution<float>(rb->getVelocity().x - var.x, rb->getVelocity().x + var.x);
	vY = new uniform_real_distribution<float>(rb->getVelocity().y - var.y, rb->getVelocity().y + var.y);
	vZ = new uniform_real_distribution<float>(rb->getVelocity().z - var.z, rb->getVelocity().z + var.z);

	// Distribuciones de posici�n
	if (!st) {
		pX = new uniform_real_distribution<float>(iniPos.x - stOffset.x, iniPos.x + stOffset.x);
		pY = new uniform_real_distribution<float>(iniPos.y - stOffset.y, iniPos.y + stOffset.y);
		pZ = new uniform_real_distribution<float>(iniPos.z - stOffset.z, iniPos.z + stOffset.z);
	}
}

// Destructora
UniformGenerator::~UniformGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

// Genera part�culas que se devuelven en la lista
list<Actor*> UniformGenerator::generateParticles(double t) {
	// Lista de part�culas
	list<Actor*> actors;

	// Generar seg�n un aleatorio
	cont += t;
	if (cont > frecuency) {
		// Variables aleatorias
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		//int lifeTime = rand() % 10 + 3;

		// Crear part�cula
		ElimState st = model->getState();
		if (!staticGenerator) {
			PxTransform* tr = new PxTransform(Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen)));
			if (st == BOUNDARIES) actors.push_back(model->clone(tr, vel));
			else actors.push_back(model->clone(tr, vel));
		}
		else {
			if (st == BOUNDARIES) actors.push_back(model->clone(model->getTransform(), vel));
			else actors.push_back(model->clone(model->getTransform(), vel));
		}

		cont = 0;
	}

	return actors;
}