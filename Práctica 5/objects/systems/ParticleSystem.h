#pragma once

#include "../physicObjects/Firework.h"
#include "../generators/particles/GaussianParticleGenerator.h"
#include "../generators/particles/UniformParticleGenerator.h"
#include "../generators/particles/FireworkGenerator.h"
#include "../generators/forces/GravityForceGenerator.h"
#include "../generators/forces/TornadoForceGenerator.h"
#include "../generators/forces/ExplosionForceGenerator.h"
#include "../generators/forces/AnchoredSpringForceGenerator.h"
#include "../generators/forces/BuoyancyForceGenerator.h"
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

enum SpringType {
	NO_SPRING,
	STATIC_SPRING,
	PARTICLES_SPRING,
	ELASTIC_BAND_SPRING,
	SLINKY_SPRING,
	BUOYANCY_SPRING
};

class ParticleSystem {
private:
	// Marcadores
	PracticeType practiceType = SPRINGS_P4;
	ParticlesType particlesType = GeneratorsType;
	ForceType forcesType = EXPLOSION;
	SpringType springType = NO_SPRING;

	// Listas de objetos
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;

	// Vector de objetos a destruir
	vector<list<Particle*>::iterator> _particlesToDelete;

	// Fuerzas
	ParticleForceRegistry* _forceRegistry = nullptr;
	vector<ForceGenerator*> _forceGenerators;

	// Generadores siempre existentes
	GravityForceGenerator* gfc;
	WindForceGenerator* wfg;
	BuoyancyForceGenerator* bfg;

public:
	// Constructora y destructora
	ParticleSystem();
	~ParticleSystem();

	// Update y keyPress
	void update(double t);
	void keyPress(char c);

	// Fuerzas
	void createForces();

	// Viento y tornado
	void createWindOrTornadoParticles();

	// Explosión
	bool createExplosion(bool expl);
	void createParticleSpheres(int n, int rad);
	
	// Cambio en spring
	void changeKSpring(char t);
	void changeMass(char t);
	void changeVolume(char t);

	// Cambios de generadores
	void showAnchoredSpring();
	void showParticlesSpring(bool el = false);
	void showSlinkySpring();
	void showBuoyancySpring();
	void resetScene();

	// Getters
	ParticleGenerator* getParticleGenerator(string name);
	ForceGenerator* getForceGenerator(string name);

	// Setters
	void setWindActive();
};

