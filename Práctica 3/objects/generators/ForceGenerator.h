#pragma once

#include "../physicObjects/Particle.h"

using namespace std;

class ForceGenerator {
private:
	string name;
	double _time = 0.0;
	double lifeTime = -1e10;

public:
	virtual ~ForceGenerator() {}

	virtual void updateForce(Particle* particle) = 0;

	inline bool updateTime(double t) {
		_time += t;
		return _time < lifeTime || lifeTime < 0.0;
	}
};
