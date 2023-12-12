#pragma once

#include "../physicObjects/Particle.h"

using namespace std;

class ForceGenerator {
protected:
	string name;
	double t = 0.0, lifeTime = -1e10;
	Vector3 pos;
	bool active;

public:
	ForceGenerator(Vector3 p) : pos(p), active(true) {};
	virtual ~ForceGenerator() {}

	virtual void updateForce(Particle* particle) = 0;

	inline void updateTime(double _t) { t += _t; }

	/*inline bool updateTime(double _t) {
		t += _t;
		return t < lifeTime || lifeTime < 0.0;
	}*/

	inline void resetTime() { t = 0; }

	inline void setActive(bool a) { active = a; }
	inline bool getActive() { return active; }
	inline string getName() { return name; }
};
