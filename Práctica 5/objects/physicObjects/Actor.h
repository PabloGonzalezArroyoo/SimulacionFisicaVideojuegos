#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../../core.hpp"
#include "../../RenderUtils.hpp"
#include <iostream>

using namespace physx;

enum Colors { RED, BLUE, YELLOW, GREEN };
enum ElimState { TIME, BOUNDARIES, BOTH, NONE };
enum ParticleShape { CIRCLE, SQUARE };

const std::vector<Vector4> colors = {
	Vector4(125, 0, 0, 1),
	Vector4(0, 125, 125, 1),
	Vector4(125, 125, 0, 1),
	Vector4(0, 125, 0, 1)
};

class Actor {
protected:
	// Render
	RenderItem* renderItem;
	PxShape* shape;
	Vector4 color;

	// Properties
	PxTransform* tr;
	float damping = 0.0998;
	Vector3 iniPos;

	// Modo
	ElimState state;
	// Tiempo
	float startTime, lifeTime;
	// Barrera
	Vector3 limits;

public:
	// Constructora y destructora
	Actor(PxTransform* t, PxShape* s, ElimState st, Vector4 c) : iniPos(tr->p), tr(t), shape(s), state(st), color(c) {
		startTime = GetLastTime();
		renderItem = new RenderItem(shape, tr, color);
	}
	~Actor() {
		renderItem->release();
		renderItem = nullptr;
	}

	virtual bool integrate(double t) = 0;

	// Comprueba si está dentro de los límites
	bool insideLimit() {
		return tr->p.y < limits.y + iniPos.y
			&& tr->p.y > -limits.y + iniPos.y
			&& tr->p.x < limits.x + iniPos.x
			&& tr->p.x > -limits.x + iniPos.x
			&& tr->p.z < limits.z + iniPos.z
			&& tr->p.z > -limits.z + iniPos.z;
	}
	void reset();

	// Cambia la forma de la partícula
	void changeShape(ParticleShape sp, Vector3 dims) {
		shape->release();
		renderItem->release();

		sp == CIRCLE ?
			shape = CreateShape(PxSphereGeometry(dims.x)) :
			shape = CreateShape(PxBoxGeometry(dims.x, dims.y, dims.z));

		renderItem = new RenderItem(shape, tr, color);
	}

	// Getters
	inline Vector3 getPos() { return Vector3(tr->p.x, tr->p.y, tr->p.z); }
	inline Vector3 getIniPos() { return iniPos; }
	inline PxTransform* getTransform() { return tr; }
	inline ElimState getState() { return state; }
	inline Vector4 getColor() { return color; }
	inline PxShape* getShape() { return shape; }
	inline float getLifeTime() { return lifeTime; }

	// Setters
	void setInvisible() { renderItem->release(); }
	inline void setColor(Vector4 c) { color = c; }
	inline void setShape(PxShape* s) { shape = s; }
	inline void setLifeTime(float l) { lifeTime = l; }
	inline void setBoundaries(Vector3 lmt) { limits = lmt; }
	inline void setPos(Vector3 p) { tr->p = p; }
};