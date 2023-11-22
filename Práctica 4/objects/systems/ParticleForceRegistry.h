#pragma once

#include <map>
#include "../generators/ForceGenerator.h"

class ParticleForceRegistry : public multimap<ForceGenerator*, Particle*> {
private:

public:
	inline void updateForces() {
		for (auto it = begin(); it != end(); it++) {
			it->first->updateForce(it->second);
			//it->first->updateForces(it->second, duration);
		}
	}

	inline void updateTime(double t) {
		for (auto it = begin(); it != end(); it++) {
			if (t != 0) it->first->updateForce(it->second);	
			else it->first->resetTime();
		}
	}

	inline void addRegistry(ForceGenerator* fg, Particle* p) {
		insert({ fg, p });
	}

	inline void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}
};