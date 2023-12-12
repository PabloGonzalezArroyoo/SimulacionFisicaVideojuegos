#include "GaussianRigidGenerator.h"

// Constructora - Setea la partícula modelo y las distribuciones según proceda
GaussianRigidGenerator::GaussianRigidGenerator(string n, RigidBody* rb, Vector3 iniPos, Vector3 var, float f, bool st,
	Vector3 stOffset) : RigidGenerator(n, rb, iniPos, var, f, st, stOffset) {

	// Partícula modelo
	rb->setPos(iniPos);

	// Distribuciones de velocidad
	vX = new normal_distribution<float>(rb->getVelocity().x, var.x);
	vY = new normal_distribution<float>(rb->getVelocity().y, var.y);
	vZ = new normal_distribution<float>(rb->getVelocity().z, var.z);

	// Distribuciones de posición
	if (!st) {
		pX = new normal_distribution<float>(iniPos.x, stOffset.x);
		pY = new normal_distribution<float>(iniPos.y, stOffset.y);
		pZ = new normal_distribution<float>(iniPos.z, stOffset.z);
	}
}

// Destructora
GaussianRigidGenerator::~GaussianRigidGenerator() {
	delete vX, vY, vZ;
	if (pX != nullptr) delete pX, pY, pZ;
	delete model;
}

// Genera partículas que se devuelven en la lista
list<RigidBody*> GaussianRigidGenerator::generateParticles(double t) {
	// Lista de partículas
	list<RigidBody*> rigidBodies;

	// Generar según un aleatorio
	cont += t;
	if (cont > frecuency) {
		// Variables aleatorias
		Vector3 vel = Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = rand() % 10 + 3;

		// Crear partícula
		rigidBodies.push_back(model->clone());
		/*RElimState st = model->getState();
		if (!staticGenerator) {
			Vector3 pos = Vector3((*pX)(gen), (*pY)(gen), (*pZ)(gen));
			if (st == R_BOUNDARIES) rigidBodies.push_back(model->clone(st, vel, pos));
			else rigidBodies.push_back(model->clone(st, vel, pos, lifeTime));
		}
		else {
			if (st == R_BOUNDARIES) rigidBodies.push_back(model->clone(st, vel, model->getPos()));
			else rigidBodies.push_back(model->clone(st, vel, model->getPos(), lifeTime));
		}*/

		cont = 0;
	}

	return rigidBodies;
}