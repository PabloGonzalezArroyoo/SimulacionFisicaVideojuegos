#pragma once

#include "../physicObjects/Particle.h"

using namespace std;

class ForceGenerator {
protected:
	string name;
	double t = 0.0;
	double lifeTime = -1e10;
	Vector3 pos;

public:
	ForceGenerator(Vector3 p) : pos(p) {};
	virtual ~ForceGenerator() {}

	virtual void updateForce(Particle* particle) = 0;

	inline void updateTime(double _t) {
		t += _t;
	}

	inline void resetTime() {
		t = 0;
	}

	/*inline bool updateTime(double _t) {
		t += _t;
		return t < lifeTime || lifeTime < 0.0;
	}*/
};
