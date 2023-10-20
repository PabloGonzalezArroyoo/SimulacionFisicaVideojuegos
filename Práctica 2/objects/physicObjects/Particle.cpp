#include "Particle.h"

// Crear particula independiente
Particle::Particle(float m, Vector3 p, Vector3 vel, Vector3 ac, int lTime, Vector4 col, PxShape* shp) :
	pos(p), gravity(Vector3(0, -10.0f, 0)) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, lTime);
	renderItem = new RenderItem(shape, &pos, color);
}

// Crear partícula sin especificar posición y tiempo de vida
Particle::Particle(float m, Vector3 vel, Vector3 ac, Vector4 col, PxShape* shp) :
	gravity(Vector3(0, -10.0f, 0)) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, 0);
	renderItem = new RenderItem(shape, &pos, color);
}

Particle::~Particle() {
	renderItem->release();
};

void Particle::setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float l, float d) {
	setMass(m); setVelocity(v); setAcceleration(a); setDamping(d); setColor(c); setShape(s); setLifeTime(l);
}

bool Particle::integrate(double t) {
	pos.p += vel * t;
	vel += (accl + gravity) * t;
	vel *= powf(damping, t);

	// Eliminar tras lifeTime segundos
	if (startTime + lifeTime < GetLastTime()) return false;
	
	return true;
}

Particle* Particle::clone(Vector3 newRanVel, Vector3 newRanAccl, float newLifeTime) const {
	return new Particle(mass, pos.p, newRanVel, newRanAccl, newLifeTime, color, shape);
}