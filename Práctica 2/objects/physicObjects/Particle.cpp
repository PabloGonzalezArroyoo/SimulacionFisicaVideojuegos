#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 ac, int lTime) : pose(pos), vel(vel) {
	startTime = GetLastTime();
	lifeTime = lTime;
	setProperties(10.0f, vel, ac, 0.99f);

	renderItem = new RenderItem(CreateShape(PxSphereGeometry(3)), &pose, Vector4(125, 125, 0, 1));
}

Particle::~Particle() {
	renderItem->release();
};

void Particle::setProperties(float m, Vector3 v, Vector3 a, float d) {
	setMass(m);
	setVelocity(v);
	setAcceleration(a);
	setDamping(d);
}

bool Particle::integrate(double t) {
	pose.p += vel * t;
	vel += accl * t;
	vel *= powf(damping, t);

	// Eliminar tras 8 segundos
	if (startTime + lifeTime < GetLastTime()) return false;
	
	return true;
}