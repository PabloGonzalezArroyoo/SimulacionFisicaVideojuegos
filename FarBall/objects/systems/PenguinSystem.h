#pragma once
#include "../gameObjects/Penguin.h"
#include "../../structure/ecs/System.h"
#include "../generators/UniformGenerator.h"
#include "../physicObjects/Particle.h"

class PenguinSystem : public System {
private:
	Penguin* penguin;
	Camera* camera;
	UniformGenerator* partGen;
	bool hit = false;
	Particle* bat;
	Particle* base;

	float updatePos;

public:
	constexpr static sysId_type id = _sys_PENGUIN;

	// Métodos virtuales
	virtual void initSystem();
	virtual void update(double t); 
	virtual void receive(const Message& m);

	void keyPressed(char key);

	void launch();
};