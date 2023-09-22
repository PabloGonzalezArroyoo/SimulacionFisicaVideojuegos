#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel) : pose(pos), vel(vel) {
	renderItem = new RenderItem(CreateShape(PxSphereGeometry(3)), &pose, Vector4(125, 125, 0, 1));
	
};

Particle::~Particle() {
	delete renderItem;
};

void Particle::integrate(double t) {
	pose.p += vel * t;
}