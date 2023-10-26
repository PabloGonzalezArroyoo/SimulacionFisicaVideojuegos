#pragma once

#include "../generators/FireworkGenerator.h"

class Firework : public Particle {
private:
	// Generador
	FireworkGenerator* generator;

	// Generaciones
	int generations;
	pair<int, int> childLimits;

public:
	Firework(Particle* m, FireworkGenerator* g, int gn, pair<int, int> cLimits);
	virtual ~Firework() {};

	list<Particle*> explode();

	virtual Firework* clone(Particle* m, pair<int, int> c) const;

	void setGenerator(FireworkGenerator* g) { generator = g; }
	void setGenerations(int gens) { generations = gens; }

	int getGenerations() { return generations; }
	pair<int, int> getChilds() { return childLimits; }
};

