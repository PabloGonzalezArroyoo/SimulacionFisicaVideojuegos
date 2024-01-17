#pragma once
#include "../gameObjects/Jetpack.h"
#include "../../structure/ecs/System.h"
#include "../generators/UniformGenerator.h"
#include "../physicObjects/Particle.h"

class ForceGenerator;
class JetpackSystem : public System {
private:
	// Referencias
	Jetpack* jetpack;
	Camera* camera;
	UniformGenerator* partGen;

	// Base inicial
	pair<Particle*, Particle*> base;

	// Generadores de dirección
	vector<ForceGenerator*> dirs;
	
	// Boleanos de control
	bool hit = false, end = false;

public:
	constexpr static sysId_type id = _sys_JETPACK;

	// Métodos virtuales
	virtual void initSystem();
	virtual void update(double t); 
	virtual void receive(const Message& m);

	// Input
	void keyPressed(char key);
	void keyReleased(char key);

	// Métodos propios
	void launch();
	void updateFuel(int x);
	void useFuel(int dir);
	void createExplosion(Vector3 pos, int n, int rad);
};