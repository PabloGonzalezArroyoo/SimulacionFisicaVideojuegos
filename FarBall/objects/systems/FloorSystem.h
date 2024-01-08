#pragma once
#include "../../structure/ecs/System.h"
#include "../physicObjects/RigidBody.h"
#include "../gameObjects/Penguin.h"

class FloorSystem : public System {
private:
	RigidBody* floor;
	Penguin* penguin = nullptr;

public:
	constexpr static sysId_type id = _sys_FLOOR;

	// Métodos esenciales
	virtual void initSystem();
	virtual void update(double t);
	virtual void receive(const Message& m);

	// Setter
	void setPenguin(Penguin* p) { penguin = p; }
};