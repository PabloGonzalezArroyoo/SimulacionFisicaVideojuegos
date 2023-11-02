#pragma once

#include "PxPhysics.h"
#include <PxPhysicsAPI.h>
#include "../../core.hpp"
#include "../../RenderUtils.hpp"
#include <iostream>

using namespace physx;

enum Colors { RED, BLUE, YELLOW, GREEN };
enum ElimState { TIME, BOUNDARIES, BOTH };

const std::vector<Vector4> colors = {
	Vector4(125, 0, 0, 1),
	Vector4(0, 125, 125, 1),
	Vector4(125, 125, 0, 1),
	Vector4(0, 125, 0, 1)
};

class Particle {
protected:
	// Render
	RenderItem* renderItem;
	PxShape* shape;
	Vector4 color;

	// Properties
	Vector3 vel, accl, iniPos, gravity = Vector3(0, -9.8f, 0);
	PxTransform pos;
	float mass, damping;

	// Modo
	ElimState state;
	// Tiempo
	float startTime, lifeTime;
	// Barrera
	Vector3 limits;

public:
	// Constructoras y destructora
	Particle(Vector3 p, Vector3 vel, ElimState st, Vector4 col, PxShape* shp, float m = 10, Vector3 ac = Vector3(0));
	//Particle(float m, Vector3 vel, Vector4 col, PxShape* shp, Vector3 ac = Vector3(0));
	~Particle();

	// Actualizar
	virtual bool integrate(double t);
	bool insideLimit();

	// Clonar partícula
	virtual Particle* clone() const;
	virtual Particle* clone(ElimState mode, Vector3 newRanVel, Vector3 newPos, float newLifeTime = 0, Vector3 newRanAccl = Vector3(0)) const;

	// Getters y setters
	void setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float d = 0.998);
	void setInvisible() { renderItem->release(); }
	#pragma region getters&setters
	inline void setMass(float m) { mass = m; }
	inline void setVelocity(Vector3 v) { vel = v; }
	inline void setAcceleration(Vector3 a) { accl = a; }
	inline void setDamping(float d) { damping = d; }
	inline void setColor(Vector4 c) { color = c; }
	inline void setShape(PxShape* s) { shape = s; }
	inline void setLifeTime(float l) { lifeTime = l; }
	inline void setBoundaries(Vector3 lmt) { limits = lmt; }
	inline void setPos(Vector3 p) { pos.p = p; }

	inline float getMass() { return mass; }
	inline Vector3 getVelocity() { return vel; }
	inline Vector3 getAcceleration() { return accl; }
	// inline float getDamping() { return damping; }
	inline Vector4 getColor() { return color; }
	inline PxShape* getShape() { return shape; }
	inline float getLifeTime() { return lifeTime; }
	inline Vector3 getPos() { return Vector3(pos.p.x, pos.p.y, pos.p.z); }
	inline PxTransform getTransform() { return pos; }
	inline ElimState getState() { return state; }
	#pragma endregion
};