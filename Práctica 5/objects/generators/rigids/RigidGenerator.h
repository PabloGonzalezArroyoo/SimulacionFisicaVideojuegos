#pragma once

#include <list>
#include <random>
#include <chrono>
#include "../../physicObjects/Actor.h"

using namespace std;

class ActorGenerator {
protected:
	// Propiedades
	string name;
	Actor* model;
	bool staticGenerator;

	// Variables
	Vector3 iniPos, meanVel, meanVar, staticOffset;
	float frecuency, cont;

	// Generador de aleatorios
	default_random_engine gen;

public:
	// rb->getVelocity()
	ActorGenerator(string n, Actor* rb, Vector3 pos, Vector3 var, float f, bool st = true, Vector3 stOffset = Vector3(0)) :
		name(n), iniPos(pos), model(rb), meanVel(0), frecuency(f), cont(0), meanVar(var), staticGenerator(st),
		staticOffset(stOffset), gen(default_random_engine(chrono::system_clock::now().time_since_epoch().count()))
	{ srand((unsigned)time); };
	virtual ~ActorGenerator() {};

	// Método abstracto
	virtual list<Actor*> generateParticles(double t) = 0;

	// Getters y setters
	inline void setModel(Actor* rb, bool mod) {
		delete model;
		model = rb->clone();
		if (mod) meanVel = rb->getPos();
	}
	inline string getName() { return name; }
	inline Actor* getModel() { return model; }
};