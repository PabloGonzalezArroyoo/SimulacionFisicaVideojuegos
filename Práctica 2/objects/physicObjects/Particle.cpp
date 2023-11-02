#include "Particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
Particle::Particle(Vector3 p, Vector3 vel, ElimState st, Vector4 col, PxShape* shp, float m, Vector3 ac) :
	pos(p), iniPos(p), state(st) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp);
	renderItem = new RenderItem(shape, &pos, color);
}

// Destructora
Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
};

// Settea las propiedades de la partícula
void Particle::setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float d) {
	setMass(m); setVelocity(v); setAcceleration(a); setDamping(d); setColor(c); setShape(s);
}

// Update
bool Particle::integrate(double t) {
	// Actualizar físicas
	pos.p += vel * t;
	vel += (accl + gravity) * t;
	vel *= powf(damping, t);

	// Eliminar tras lifeTime segundos
	if (state == TIME && (startTime + lifeTime < GetLastTime())) return false;
	// Eliminar si ha sobrepasado el límite
	else if (state == BOUNDARIES && !insideLimit()) return false;
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	else if (state == BOTH && (startTime + lifeTime < GetLastTime() || !insideLimit())) return false;
	
	return true;
}

bool Particle::insideLimit() {
	return pos.p.y < limits.y + iniPos.y
		&& pos.p.y > -limits.y + iniPos.y
		&& pos.p.x < limits.x + iniPos.x
		&& pos.p.x > -limits.x + iniPos.x
		&& pos.p.z < limits.z + iniPos.z
		&& pos.p.z > -limits.z + iniPos.z;
}

// Clona la partícula actual modificando velocidad, aceleración y tiempo de vida
Particle* Particle::clone(ElimState mode, Vector3 newRanVel, Vector3 newPos, float newLifeTime, Vector3 newRanAccl) const {
	Particle* p = new Particle(newPos, newRanVel, mode, color, shape, mass, newRanAccl);
	p->setLifeTime(newLifeTime);
	p->setBoundaries(limits);
	return p;
}

// Clona la partícula actual
Particle* Particle::clone() const {
	Particle* p = new Particle(pos.p, vel, state, color, shape, mass, accl);
	p->setLifeTime(lifeTime);
	p->setBoundaries(limits);
	return p;
}