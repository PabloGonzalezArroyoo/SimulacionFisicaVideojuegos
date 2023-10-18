#pragma once

#include <list>
#include <random>
#include <chrono>
#include "../physicObjects/Particle.h"
using namespace std;

class ParticleGenerator {
private:
	string name;
	int probability;
	Particle* _model;
	std::default_random_engine gen;

public:
	ParticleGenerator(Vector3 medSpeed, Vector3 medVar, int prob);
	~ParticleGenerator();

	void setParticle(Particle* model);

	virtual list<Particle*> generateParticles();

	inline string getName() { return name; }
};