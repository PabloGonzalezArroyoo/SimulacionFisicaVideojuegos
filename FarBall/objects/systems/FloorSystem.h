#pragma once
#include "../../structure/ecs/System.h"
#include "../physicObjects/RigidBody.h"
#include "../physicObjects/Particle.h"
#include "../gameObjects/Jetpack.h"

class FloorSystem : public System {
private:
	RigidBody* floor;
	Particle* shadow;
	Jetpack* jetpack;

public:
	constexpr static sysId_type id = _sys_FLOOR;

	// M�todos esenciales
	virtual void initSystem();
	virtual void update(double t);
	virtual void receive(const Message& m);
};