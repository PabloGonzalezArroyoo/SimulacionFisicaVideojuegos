#pragma once
#include "../physicObjects/RigidBody.h"
#include "../physicObjects/Particle.h"
#include <vector>

using namespace std;

class Penguin : public RigidBody {
private:
	bool isLaunched;
	vector<Particle*> decorations;

public:
	Penguin(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m);
	~Penguin() {};

	virtual void integrate(double t);
	void keyPressed(char key);

	void launch();
};