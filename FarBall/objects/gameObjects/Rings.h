#pragma once

#include "../physicObjects/Particle.h"
#include "../../structure/ecs/Manager.h"
#include <vector>

using namespace std;

class Rings {
private:
	Manager* mng;
	vector<Particle*> parts;

public:
	Rings(Vector3 p, Vector4 col, Manager* j);
	~Rings();

	// Actualizar
	bool integrate(double t);
};

