#include "Particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
Particle::Particle(Vector3 p, Vector3 vel, ElimState st, Vector4 col, PxShape* shp, float m) : 
	Actor(PxTransform(p), shp, st, col), force(Vector3(0)) {

	setMass(m);
	setVelocity(vel);
	renderItem = new RenderItem(shape, &tr, color);
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

// Update
void Particle::integrate(double t) {
	// Calcular aceleración y velocidad
	addForce(vel);
	Vector3 resulting_accel = force * getInvMass();
	vel += resulting_accel * t;
	vel *= powf(damping, t);

	// Actualizar posición
	tr.p += vel * t;

	// Borrar fuerza 
	//clearForce();

	// Eliminar tras lifeTime segundos
	if (state == TIME && (startTime + lifeTime < GetLastTime())) setAlive(false);
	// Eliminar si ha sobrepasado el límite
	else if (state == BOUNDARIES && !insideLimit()) setAlive(false);
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	else if (state == BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) setAlive(false);
}

// Devuelve la partícula a su estado inicial
void Particle::reset() {
	clearForce();
	setPos(iniPos);
	setVelocity(Vector3(0));
}

// Clona la partícula actual modificando velocidad, aceleración y tiempo de vida
Particle* Particle::clone(ElimState mode, Vector3 newRanVel, Vector3 newPos, float newLifeTime) const {
	Particle* p = new Particle(newPos, newRanVel, mode, color, shape, mass);
	p->setLifeTime(newLifeTime);
	p->setBoundaries(limits);
	return p;
}

// Clona la partícula actual
Particle* Particle::clone() const {
	Particle* p = new Particle(tr.p, vel, state, color, shape, mass);
	p->setLifeTime(lifeTime);
	p->setBoundaries(limits);
	return p;
}

Particle* Particle::clone(PxTransform t, Vector3 v) const {
	Particle* p = new Particle(tr.p, v, state, color, shape, mass);
	p->setLifeTime(lifeTime);
	p->setBoundaries(limits);
	return p;
}