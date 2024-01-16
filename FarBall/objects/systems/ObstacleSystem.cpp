#include "ObstacleSystem.h"
#include "../../structure/ecs/Manager.h"

void ObstacleSystem::initSystem() {
	posBg = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600, -50, 300);
	posFg = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600,   0, -160);
	posRings = mngr->getHandler(_hdlr_JETPACK)->getPos() + Vector3(600, 20, 0);
}

void ObstacleSystem::update(double t) {
	// Generar nuevos si se supera la distancia del anterior generado
	int penActX = mngr->getHandler(_hdlr_JETPACK)->getPos().x;
	if (penActX > prevPenXBg + 100) {
		createBgObject(penActX);
		prevPenXBg = penActX;
	}

	if (penActX > prevPenXRings + 200) {
		createRing(penActX);
		prevPenXRings = penActX;
	}

	// Actualizar obstáculos y borrar si han pasado del pinguino
	for (Actor* a : mngr->getActors(_grp_BACKGROUND)) {
		a->integrate(t);
		if (a->getPos().x < penActX - 200) a->setAlive(false);
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
	// Fondo
	int height = rand() % 60 + 20;
	RigidBody* stBg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posBg + Vector3(x, 0, 0)),
		CreateShape(PxBoxGeometry(30, height, 30)), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f), 1, false);

	// Frente
	height = rand() % 20 + 10;
	RigidBody* stFg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posFg + Vector3(x, 0, 0)),
		CreateShape(PxBoxGeometry(30, height, 30)), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f), 1, false);

	// Añadir a la estructura
	mngr->addActor(_grp_BACKGROUND, stFg);
	mngr->addActor(_grp_BACKGROUND, stBg);
}

void ObstacleSystem::createRing(int x) {
	int height = rand() % 80 + 20;
	rings.push_back(new Rings(posRings + Vector3(x, height, 0), colors[YELLOW], mngr));
}