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
	Vector3 iniPos, meanVel, meanVar, staticOffset;
	float frecuency, cont;

	// Generador de aleatorios
	default_random_engine gen;

public:
	// Constructora y destructora
	ParticleGenerator(string n, Particle* p, Vector3 pos, Vector3 var, float f, bool st = true, Vector3 stOffset = Vector3(0));
	~ParticleGenerator();

	// Método abstracto
	virtual list<Particle*> generateParticles(double t) = 0;

	// Getters y setters
	inline void setParticle(Particle* m, bool mod);
	inline string getName() { return name; }
	Particle* getModel() { return model; }
};