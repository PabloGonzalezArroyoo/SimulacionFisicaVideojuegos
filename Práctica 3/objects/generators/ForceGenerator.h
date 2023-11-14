#pragma once

#include "../physicObjects/Particle.h"

using namespace std;

class ForceGenerator {
private:
	string name;
	double time = 0.0;
	double lifeTime = -1e10;

public:
	virtual ~ForceGenerator() {}

	virtual void updateForce(Particle* particle) = 0;

	inline bool updateTime(double t) {
		time += t;
		return time < lifeTime || lifeTime < 0.0;
	}
};
