#pragma once

#include "../physicObjects/Firework.h"
#include "../generators/GaussianParticleGenerator.h"
#include "../generators/UniformParticleGenerator.h"
#include "../generators/FireworkGenerator.h"
#include "../generators/GravityForceGenerator.h"
#include "../generators/TornadoForceGenerator.h"
#include "../generators/ExplosionForceGenerator.h"
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
	WIND, WIND2, WIND3, WIND4,
	TORNADO,
	EXPLOSION
};

class ParticleSystem {
private:
	// Marcadores
	PracticeType practiceType = FORCES_P3A1;
	ParticlesType particlesType = GeneratorsType;
	ForceType forcesType = EXPLOSION;

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

	// Fuerzas
	void createForces();

	// Viento y tornado
	void createWindOrTornadoParticles();

	// Explosión
	void createExplosion(bool expl);
	void createParticleSpheres(int n, int rad);
	
	// Getters
	ParticleGenerator* getParticleGenerator(string name);
};

