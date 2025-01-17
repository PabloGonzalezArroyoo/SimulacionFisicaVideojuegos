#pragma once

#include "ForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator {
private:
	float height, volume, liquidDensity, gravity = 9.8;

	Particle* liquidParticle;
	
public:
	BuoyancyForceGenerator(Vector3 pos, float h, float v, float d);
	virtual ~BuoyancyForceGenerator();

	virtual void updateForce(Particle* particle);

	void setVolume(float v) { volume = v; }
	float getVolume() { return volume; }
	void setHeight(float h) { height = h; }
	float getHeight() { return height; }
};

