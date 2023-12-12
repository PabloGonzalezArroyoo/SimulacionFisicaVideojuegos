#include "FireworkGenerator.h"
#include "../../physicObjects/Firework.h"

FireworkGenerator::FireworkGenerator(string n, Particle* m, Vector3 pos, Vector3 var) : 
	UniformParticleGenerator(n, m, pos, var), initiateGenerator(true) {

}

FireworkGenerator::~FireworkGenerator() {
	if (vX != nullptr) {
		delete vX; delete vY; delete vZ;
	}
}

void FireworkGenerator::recalculateDistributions(Vector3 vel) {
	if (vX != nullptr) {
		delete vX; delete vY; delete vZ;
	}

	vX = new uniform_real_distribution<float>(vel.x, vel.x + meanVar.x);
	vY = new uniform_real_distribution<float>(vel.y, vel.y + meanVar.y);
	vZ = new uniform_real_distribution<float>(vel.z, vel.z + meanVar.z);
}

Vector3 FireworkGenerator::obtainDistributionVelValues() {
	return Vector3((*vX)(gen), (*vY)(gen), (*vZ)(gen));
}

list<Particle*> FireworkGenerator::generateParticles(double t) {
	list<Particle*> lista;

	if (initiateGenerator) {
		Firework* fr = static_cast<Firework*>(model);
		model->setPos(iniPos);
		fr = new Firework(model, this, fr->getGenerations(), fr->getChilds(), fr->getChangeColors());
		fr->setVelocity({ 0, meanVel.y, 0 });
		lista.push_back(fr);
		initiateGenerator = false;
	}

	return lista;
}