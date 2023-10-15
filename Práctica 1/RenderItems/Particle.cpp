#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel) : pose(pos), vel(vel) {
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
	
	return true;
}