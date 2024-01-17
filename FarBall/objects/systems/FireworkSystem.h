#pragma once

#include "../../structure/ecs/System.h"
#include "../generators/FireworkGenerator.h"
#include "../physicObjects/Firework.h"

class GravityForceGenerator;
class FireworkSystem : public System {
private:
	int points;
	pair<FireworkGenerator*, FireworkGenerator*> fireworks;
	GravityForceGenerator* gfg;


public:
	constexpr static sysId_type id = _sys_FIREWORKS;

	// Métodos virtuales
	virtual void initSystem();
	virtual void update(double t);
	virtual void receive(const Message& m);
};