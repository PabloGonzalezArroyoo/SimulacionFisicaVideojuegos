#pragma once

#include "SpringForceGenerator.h"
#include "../../core.hpp"

class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(Vector3 pos, double _k, double rl);

	~AnchoredSpringForceGenerator();
};

