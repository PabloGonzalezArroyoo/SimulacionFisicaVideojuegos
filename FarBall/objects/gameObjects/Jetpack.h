#pragma once
#include "../physicObjects/RigidBody.h"
#include "../../structure/ecs/Constants.h"
#include <vector>

using namespace std;

class Jetpack : public RigidBody {
private:
	bool isLaunched;
	int fuel = JETPACK_FUEL;

public:
	Jetpack(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m);
	~Jetpack() {};

	virtual void integrate(double t);
	void useFuel();
	void setFuel(int f);
	inline int getFuel() { return fuel; }

	void launch();
};