#pragma once

#include "../physicObjects/Particle.h"
#include "../generators/GaussianParticleGenerator.h"
#include <list>

using namespace std;

class ParticleSystem {
private:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	vector<list<Particle*>::iterator> _particlesToDelete;

public:
	ParticleSystem();
	~ParticleSystem();

	void update(double t);
	
	ParticleGenerator* getParticleGenerator(string name);

	void generateFireworkSystem();
};

