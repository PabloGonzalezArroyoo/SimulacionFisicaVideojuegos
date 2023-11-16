#pragma once

#include "ForceGenerator.h"
#include "../../core.hpp"

class WindForceGenerator : public ForceGenerator {
protected:
	// k1 -> velocidad, k2 -> velocidad cuadrática
	float k1, k2;
	Vector3 vel;
	float size;

	RenderItem* renderItem;

public:
	~WindForceGenerator() { renderItem->release(); };
	WindForceGenerator(Vector3 p, Vector3 v, float s, Vector4 c, const float _k1, const float _k2 = 0);

	virtual void updateForce(Particle* particle);
	virtual bool insideLimit(Vector3 p);

	inline void setInvisible() { renderItem->release(); }
	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
};