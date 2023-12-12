#include "AnchoredSpringForceGenerator.h"


AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3 pos, double _k, double rl) : SpringForceGenerator(pos, _k, rl, nullptr) {
	name = "anchoredSpring";
	other = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)), 1e6);
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	delete other;
}