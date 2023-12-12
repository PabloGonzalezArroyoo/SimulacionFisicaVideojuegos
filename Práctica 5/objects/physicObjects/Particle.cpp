#include "Particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
Particle::Particle(Vector3 p, Vector3 vel, ElimState st, Vector4 col, PxShape* shp, float m) :
	pos(p), iniPos(p), state(st), force(Vector3(0)) {
	
	startTime = GetLastTime();
	setProperties(m, vel, col, shp);
	renderItem = new RenderItem(shape, &pos, color);
}

// Destructora
Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
};

// Settea las propiedades de la part�cula
void Particle::setProperties(float m, Vector3 v, Vector4 c, PxShape* s, float d) {
	setMass(m); setVelocity(v); setDamping(d); setColor(c); setShape(s);
}

// Update
bool Particle::integrate(double t) {
	// Calcular aceleraci�n y velocidad
	Vector3 resulting_accel = force * getInvMass();
	vel += resulting_accel * t;
	vel *= powf(damping, t);

	// Actualizar posici�n
	pos.p += vel * t;

	// Borrar fuerza 
	clearForce();

	// Eliminar tras lifeTime segundos
	if (state == TIME && (startTime + lifeTime < GetLastTime())) return false;
	// Eliminar si ha sobrepasado el l�mite
	else if (state == BOUNDARIES && !insideLimit()) return false;
	// Eliminar tras lifeTime segundos o si ha sobrepasado el l�mite
	else if (state == BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) return false;
	
	return true;
}

// Comprueba si est� dentro de los l�mites
bool Particle::insideLimit() {
	return pos.p.y < limits.y + iniPos.y
		&& pos.p.y > -limits.y + iniPos.y
		&& pos.p.x < limits.x + iniPos.x
		&& pos.p.x > -limits.x + iniPos.x
		&& pos.p.z < limits.z + iniPos.z
		&& pos.p.z > -limits.z + iniPos.z;
}

// Devuelve la part�cula a su estado inicial
void Particle::reset() {
	clearForce();
	setPos(iniPos);
	setVelocity(Vector3(0));
}

// Cambia la forma de la part�cula
void Particle::changeShape(ParticleShape sp, Vector3 dims) {
	shape->release();
	renderItem->release();

	sp == CIRCLE ?
		shape = CreateShape(PxSphereGeometry(dims.x)) :
		shape = CreateShape(PxBoxGeometry(dims.x, dims.y, dims.z));

	renderItem = new RenderItem(shape, &pos, color);
}

// Clona la part�cula actual modificando velocidad, aceleraci�n y tiempo de vida
Particle* Particle::clone(ElimState mode, Vector3 newRanVel, Vector3 newPos, float newLifeTime) const {
	Particle* p = new Particle(newPos, newRanVel, mode, color, shape, mass);
	p->setLifeTime(newLifeTime);
	p->setBoundaries(limits);
	return p;
}

// Clona la part�cula actual
Particle* Particle::clone() const {
	Particle* p = new Particle(pos.p, vel, state, color, shape, mass);
	p->setLifeTime(lifeTime);
	p->setBoundaries(limits);
	return p;
}