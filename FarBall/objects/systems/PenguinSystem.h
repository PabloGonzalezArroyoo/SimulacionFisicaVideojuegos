#pragma once
#include "../gameObjects/Penguin.h"
#include "../../structure/ecs/System.h"

class PenguinSystem : public System {
private:
	Penguin* penguin;
	Camera* camera;

public:
	constexpr static sysId_type id = _sys_PENGUIN;

	// Métodos virtuales
	virtual void initSystem();
	virtual void update(double t); 
	virtual void receive(const Message& m);

	void keyPressed(char key);

	// Getters
	Penguin* getPenguin() { return penguin; }
};