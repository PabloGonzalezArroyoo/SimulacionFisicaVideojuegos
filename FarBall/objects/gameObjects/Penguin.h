#pragma once
#include "../physicObjects/RigidBody.h"

class Penguin : public RigidBody {
private:
	
public:
	Penguin(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m);
	~Penguin() {};

	void keyPressed(char key);
};