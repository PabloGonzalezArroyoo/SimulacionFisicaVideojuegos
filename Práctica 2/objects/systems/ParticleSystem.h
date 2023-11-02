#pragma once

#include "../physicObjects/Firework.h"
#include "../generators/GaussianParticleGenerator.h"
#include "../generators/UniformParticleGenerator.h"
#include "../generators/FireworkGenerator.h"
#include <list>

using namespace std;

class ParticleSystem {
private:
	// Listas de objetos
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	// Vector de objetos a destruir
	vector<list<Particle*>::iterator> _particlesToDelete;

public:
	// Constructora y destructora
	ParticleSystem();
	~ParticleSystem();

	// Update
	void update(double t);
	
	// Getters
	ParticleGenerator* getParticleGenerator(string name);
};

