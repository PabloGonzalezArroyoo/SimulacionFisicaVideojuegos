#include "ObstacleSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../generators/ForceGenerator.h"

void ObstacleSystem::initSystem() {
	// Ajustar posiciones de cada elemento
	posBg = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600, -50, 300);
	posFg = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600,   0, -160);
	posRings = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600, 20, 0);
}

void ObstacleSystem::update(double t) {
	// Generar nuevos objetos de fondo si se supera la distancia del anterior generado
	int penActX = mngr->getHandler(_hdlr_JETPACK)->getPos().x;
	if (penActX > prevPenXBg + 100) {
		createBgObject(penActX);
		prevPenXBg = penActX;
	}

	// Generar nuevos anillos si se supera una distancia
	if (penActX > prevPenXRings + 400) {
		createRing(penActX);
		prevPenXRings = penActX;
	}

	// Actualizar obstáculos y borrar si han pasado del jetpack o los ha atravesado
	for (Actor* a : mngr->getActors(_grp_BACKGROUND)) {
		a->integrate(t);
		if (a->getPos().x < penActX - 200) {
			a->setAlive(false);
			if (a->getVelocity().y != 0) {
				mngr->getForceRegistry()->deleteActorRegistry(a);
				mngr->getForceRegistry()->deleteForceRegistry(generators.front());
				generators.pop();
			}
		}
	}
	for (auto it = rings.begin(); it != rings.end(); it++) {
		if (!(*it)->integrate(t)) ringsToDelete.push_back(it);
	}
	for (int i = 0; i < ringsToDelete.size(); i++) {
		delete* ringsToDelete[i];
		rings.erase(ringsToDelete[i]);
	}
	ringsToDelete.clear();
}

// Crear objetos del background y el foreground
void ObstacleSystem::createBgObject(int x) {
	// Fondo con flotación ---
	int height = rand() % 60 + 20;
	
	// Partícula negra
	Particle* stBg = new Particle(posBg + Vector3(x, 0, 0), Vector3(0), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f),
		CreateShape(PxBoxGeometry(30, height, 30)), 1);
	// Sólido esférico o cuadrado
	RigidBody* rg;
	if (height > 30) rg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posBg + Vector3(x, height + 20, 0)),
			CreateShape(PxBoxGeometry(10, 10, 10)), NONE, Vector4(255, 0, 255, 1.0f), 2);
	else rg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posBg + Vector3(x, height + 20, 0)),
			CreateShape(PxSphereGeometry(10)), NONE, Vector4(255, 0, 255, 1.0f), 2);
	// Generador de fuerza
	BuoyancyForceGenerator* bfg = new BuoyancyForceGenerator(posBg + Vector3(x, height, 0), 20, 10, 1);
	bfg->getLiquidParticle()->setInvisible();

	// Frente ---
	height = rand() % 20 + 10;
	RigidBody* stFg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posFg + Vector3(x, 0, 0)),
		CreateShape(PxBoxGeometry(30, height, 30)), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f), 1, false);

	// Añadir a la estructura ---
	mngr->addActor(_grp_BACKGROUND, stFg);
	mngr->addActor(_grp_BACKGROUND, stBg);
	mngr->addActor(_grp_BACKGROUND, rg);
	mngr->getForceRegistry()->addRegistry(bfg, rg);	
	generators.push(bfg);
}

// Crear anillos
void ObstacleSystem::createRing(int x) {
	int height = rand() % 80;
	rings.push_back(new Rings(posRings + Vector3(x, height, 0), colors[YELLOW], mngr));
}