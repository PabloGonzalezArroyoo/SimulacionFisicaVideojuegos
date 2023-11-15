
#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(Vector3 p, Vector3 v, float s, const float _k1, const float _k2) : pos(p), vel(v), size(s),
	k1(_k1), k2(_k2) {
	/*PxShape* shape = CreateShape(PxBoxGeometry(siz, size, size));
	Vector4 color = Vector4(125, 125, 125, 1);
	PxTransform* transform = &PxTransform(pos);
	RenderItem* renderItem = new RenderItem(shape, transform, color);*/
}

void WindForceGenerator::updateForce(Particle* particle) {
	if (fabs(particle->getInvMass()) > 1e-10 && insideLimit(particle->getPos())) {
		/*dragCoef = k1 * v.normalize(); + k2 * v.normalize(); * v.normalize();;
		Vector3 dragF = -v * dragCoef;*/

		Vector3 diffVel = vel - particle->getVelocity();
		Vector3 dragF = k1 * diffVel + k2 * diffVel.magnitude() * diffVel;

		//cout << dragF.x << " " << dragF.y << " " << dragF.z << endl;
		particle->addFroce(dragF);
	}
}

bool WindForceGenerator::insideLimit(Vector3 p) {
	return pos.y < size + pos.y
		&& pos.y > -size + pos.y
		&& pos.x < size + pos.x
		&& pos.x > -size + pos.x
		&& pos.z < size + pos.z
		&& pos.z > -size + pos.z;
}