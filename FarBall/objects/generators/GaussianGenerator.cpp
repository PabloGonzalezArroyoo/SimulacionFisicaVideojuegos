#include "GaussianGenerator.h"

// Constructora - Setea la part�cula modelo y las distribuciones seg�n proceda
GaussianGenerator::GaussianGenerator(string n, Actor* rb, Vector3 iniPos, Vector3 var, float f, bool st,
	Vector3 stOffset) : ActorGenerator(n, rb, iniPos, var, f, st, stOffset) {

	// Part�cula modelo
	rb->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new normal_distribution<float>(rb->getVelocity().x, var.x);
	vY = new normal_distribution<float>(rb->getVelocity().y, var.y);
	vZ = new normal_distribution<float>(rb->getVelocity().z, var.z);

	// Distribuciones de posici�n
	if (!st) {
		pX = new normal_distribution<float>(iniPos.x, stOffset.x);
		pY = new normal_distribution<float>(iniPos.y, stOffset.y);
		pZ = new normal_distribution<float>(iniPos.z, stOffset.z);
	}
}

// Destructora
GaussianGenerator::~GaussianGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

// Genera part�culas que se devuelven en la lista
list<Actor*> GaussianGenerator::generateParticles(double t) {
	// Lista de part�culas
	list<Actor*> actors;

	// Generar seg�n un aleatorio
	cont += t;
	if (cont > frecuency) {
		// Variables aleatorias
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		int lifeTime = rand() % 10 + 3;

		// Crear part�cula
		ElimState st = model->getState();
		if (!staticGenerator) {
			PxTransform tr = PxTransform(Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen)));
			if (st == BOUNDARIES) actors.push_back(model->clone(tr, vel));
			else if (st == TIME) {
				Actor* ac = model->clone(tr, vel);
				ac->setLifeTime(lifeTime);
				actors.push_back(ac);
			}
			else actors.push_back(model->clone(tr, vel));
		}
		else {
			if (st == BOUNDARIES) actors.push_back(model->clone(model->getTransform(), vel));
			else if (st == TIME) {
				Actor* ac = model->clone(model->getTransform(), vel);
				ac->setLifeTime(lifeTime);
				actors.push_back(ac);
			}
			else actors.push_back(model->clone(model->getTransform(), vel));
		}

		cont = 0;
	}

	return actors;
}