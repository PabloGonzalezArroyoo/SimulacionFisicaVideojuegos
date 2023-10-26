#include "Particle.h"

// Constructora - Crea una particula definiendo todas sus propiedades
Particle::Particle(Vector3 p, Vector3 vel, int lTime, Vector4 col, PxShape* shp, float m, Vector3 ac) :
	pos(p) {
	
	startTime = GetLastTime();
	setProperties(m, vel, ac, col, shp, lTime);
	renderItem = new RenderItem(shape, &pos, color);
}




// Destructora
Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
};

// Settea las propiedades de la partícula
void Particle::setProperties(float m, Vector3 v, Vector3 a, Vector4 c, PxShape* s, float l, float d) {
	setMass(m); setVelocity(v); setAcceleration(a); setDamping(d); setColor(c); setShape(s); setLifeTime(l);
}

// Update
bool Particle::integrate(double t) {
	// Actualizar físicas
	pos.p += vel * t;
	vel += (accl + gravity) * t;
	vel *= powf(damping, t);

	// Eliminar tras lifeTime segundos
	if (startTime + lifeTime < GetLastTime()) return false;
	// Eliminar tras lifeTime segundos o si ha sobrepasado el límite
	//if (startTime + lifeTime < GetLastTime() || !insideLimit()) return false;
	
	return true;
}

bool Particle::insideLimit() {
	return pos.p.y < vLimit && pos.p.y > -vLimit && pos.p.x < xLimit && pos.p.x > -xLimit;
}

// Clona la partícula actual modificando velocidad, aceleración y tiempo de vida
Particle* Particle::clone(Vector3 newRanVel, float newLifeTime, Vector3 newPos, Vector3 newRanAccl) const {
	return new Particle(newPos, newRanVel, newLifeTime, color, shape, mass, newRanAccl);
}

// Clona la partícula actual
Particle* Particle::clone() const {
	return new Particle(pos.p, vel, lifeTime, color, shape, mass, accl);
}