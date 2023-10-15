#pragma once

#include <list>
#include "../physicObjects/Particle.h"
using namespace std;

class ParticleGenerator {
private:
	string name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* _model;

public:
	ParticleGenerator();
	~ParticleGenerator();

	void setParticle(Particle* model);

	virtual list<Particle*> generateParticles();
};