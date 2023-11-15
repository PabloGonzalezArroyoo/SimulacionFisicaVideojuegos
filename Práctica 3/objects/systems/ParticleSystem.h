#pragma once

#include "../physicObjects/Firework.h"
#include "../generators/GaussianParticleGenerator.h"
#include "../generators/UniformParticleGenerator.h"
#include "../generators/FireworkGenerator.h"
#include "../generators/GravityForceGenerator.h"
#include "../generators/WindForceGenerator.h"
#include <list>
#include "ParticleForceRegistry.h"

using namespace std;

enum PracticeType {
	PARTICLES_P2A1,
	FIREWORKS_P2A2,
	FORCES_P3A1
};

enum ParticlesType {
	GeneratorsType,
	FireworksType
};

enum ForceType {
	GRAVITY_DOWN,
	GRAVITY_UP,
	WIND
};

class ParticleSystem {
private:
	PracticeType practiceType = FORCES_P3A1;
	ParticlesType particlesType = GeneratorsType;

	// Listas de objetos
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	// Vector de objetos a destruir
	vector<list<Particle*>::iterator> _particlesToDelete;

	// Fuerzas
	ParticleForceRegistry* _forceRegistry;
	vector<ForceGenerator*> _forceGenerators;

public:
	// Constructora y destructora
	ParticleSystem();
	~ParticleSystem();

	// Update
	void update(double t);
	
	// Getters
	ParticleGenerator* getParticleGenerator(string name);
};

