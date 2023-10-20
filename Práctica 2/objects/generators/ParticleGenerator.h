#pragma once

#include <list>
#include <random>
#include <chrono>
#include "../physicObjects/Particle.h"

using namespace std;

class ParticleGenerator {
protected:
	string name;
	Particle* model;

	Vector3 iniPos, meanVel, meanVar;
	float probability;

public:
	ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob);
	~ParticleGenerator();

	void setParticle(Particle* model);

	virtual list<Particle*> generateParticles() = 0;

	inline string getName() { return name; }
};