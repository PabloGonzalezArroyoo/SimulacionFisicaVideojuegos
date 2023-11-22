#pragma once

#include "../physicObjects/Firework.h"
#include "../generators/GaussianParticleGenerator.h"
#include "../generators/UniformParticleGenerator.h"
#include "../generators/FireworkGenerator.h"
#include "../generators/GravityForceGenerator.h"
#include "../generators/TornadoForceGenerator.h"
#include "../generators/ExplosionForceGenerator.h"
#include "../generators/AnchoredSpringForceGenerator.h"
#include <list>
#include "ParticleForceRegistry.h"

using namespace std;

enum PracticeType {
	PARTICLES_P2A1,
	FIREWORKS_P2A2,
	FORCES_P3,
	SPRINGS_P4
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

enum SpringGen {
	GRAVITY_GEN,
	WIND_GEN,
	STATIC_SPRING
};

class ParticleSystem {
private:
	// Marcadores
	PracticeType practiceType = SPRINGS_P4;
	ParticlesType particlesType = GeneratorsType;
	ForceType forcesType = EXPLOSION;

	// Listas de objetos
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	// Vector de objetos a destruir
	vector<list<Particle*>::iterator> _particlesToDelete;

	// Fuerzas
	ParticleForceRegistry* _forceRegistry = nullptr;
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

	// Explosi�n
	void createExplosion(bool expl);
	void createParticleSpheres(int n, int rad);
	
	// Getters
	ParticleGenerator* getParticleGenerator(string name);
	ForceGenerator* getForceGenerator(string name);

	// Setters
	inline void setSpringK(SpringGen gen, float _k) { static_cast<SpringForceGenerator*>(_forceGenerators[gen])->setK(_k); }
	inline void setWindActive(SpringGen gen, bool a) { _forceGenerators[gen]->setActive(a); }
};

