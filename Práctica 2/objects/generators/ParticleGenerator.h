#pragma once

#include <list>
#include <random>
#include <chrono>
#include "../physicObjects/Particle.h"

using namespace std;

class ParticleGenerator {
protected:
	// Propiedades
	string name;
	Particle* model;
	bool staticGenerator;

	// Variables
	Vector3 iniPos, meanVel, meanVar;
	float probability;

	// Generador de aleatorios
	default_random_engine gen;

public:
	// Constructora y destructora
	ParticleGenerator(Vector3 iniPos, Vector3 medSpeed, Vector3 medVar, float prob, bool st);
	~ParticleGenerator();

	// Método abstracto
	virtual list<Particle*> generateParticles() = 0;

	// Getters y setters
	inline void setParticle(Particle* m) { model = m; }
	inline string getName() { return name; }
};