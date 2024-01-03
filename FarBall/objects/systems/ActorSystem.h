#pragma once

#include "../generators/GaussianGenerator.h"
#include "../generators/UniformGenerator.h"
#include "../physicObjects/RigidBody.h"
#include "../generators/ForceGenerator.h"
#include "ForceRegistry.h"
#include <algorithm>

enum State {
	A_NONE,
	A_GRAVITY,
	A_GAUSSIAN, A_UNIFORM,
	A_WIND, A_TORNADO,
	A_EXPLOSION,
	A_ANCHORED, A_SPRING, A_SLINKY, A_BUOYANCY
};

class ActorSystem {
private:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	int rigidCounter, rigidLimit = -1;
	RigidBody* floor = nullptr;
	State state;

	// Listas de objetos, generadores y fuerzas
	list<Actor*> _actors;
	list<ActorGenerator*> _actor_generators;
	list<ForceGenerator*> _force_generators;
	ForceRegistry* _forceRegistry = nullptr;

	// Vector de objetos a destruir
	vector<list<Actor*>::iterator> _actorsToDelete;

public:
	// Constructora y destructora
	ActorSystem(PxPhysics* gPhysics, PxScene* gScene);
	~ActorSystem();

	virtual void update(double t);
	virtual void keyPress(char c);
	void attachForces(list<Actor*>& l);

	// Crear generadores y fuerzas
	void resetScene();
	void createGravity(int acts, int rad);
	void createGaussian(bool st, Vector3 pos = Vector3(0), Vector3 var = Vector3(20), float spTime = 0, Vector3 offset = Vector3(50));
	void createUniform(bool st, Vector3 pos = Vector3(0), Vector3 var = Vector3(20), float spTime = 0, Vector3 offset = Vector3(50));
	void createWind();
	void createTornado();
	void createExplosion(int acts, int rad, State st);
	void createSphere(int acts, int rad);
	void createAnchored();
	void createSpring(bool el);
	void createSlinky();
	void createBuoyancy();
	void createParticleGaussian();

	ForceGenerator* getGenerator(string name);
	inline void addFloor() {
		if (floor == nullptr) floor = new RigidBody(gPhysics, gScene, PxTransform(Vector3(-20)),
			CreateShape(PxBoxGeometry(400, 2, 400)), NONE, colors[BLUE], 1000, false);
	}
	inline void deleteFloor() {
		if (floor != nullptr) { delete floor; floor = nullptr; }
	}
	bool checkIfDeletedIsIn(list<Actor*>::iterator& it);
};