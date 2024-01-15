#include "ObstacleSystem.h"
#include "../../structure/ecs/Manager.h"

void ObstacleSystem::initSystem() {
	posBg = mngr->getHandler(_hdlr_PENGUIN)->getPos() + Vector3(600, -50, 300);
	posFg = mngr->getHandler(_hdlr_PENGUIN)->getPos() + Vector3(600,   0, -160);
}

void ObstacleSystem::update(double t) {
	// Generar nuevos si se supera la distancia del anterior generado
	int penActX = mngr->getHandler(_hdlr_PENGUIN)->getPos().x;
	if (penActX > prevPenX + 100) {
		createBgObject(penActX);
		prevPenX = penActX;
	}

	if (penActX > prevPenX + rand() % 200 + 200) {
		//createObstacle(penActX);
	}

	// Actualizar obstáculos y borrar si han pasado del pinguino
	for (Actor* a : mngr->getActors(_grp_BACKGROUND)) {
		a->integrate(t);
		if (a->getPos().x < penActX - 200) a->setAlive(false);
	}
}

// Crear objetos del background y el foreground
void ObstacleSystem::createBgObject(int x) {
	int height = rand() % 60 + 20;
	RigidBody* stBg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posBg + Vector3(x, 0, 0)),
		CreateShape(PxBoxGeometry(30, height, 30)), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f), 1, false);

	height = rand() % 20 + 10;
	RigidBody* stFg = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(posFg + Vector3(x, 0, 0)),
		CreateShape(PxBoxGeometry(30, height, 30)), NONE, Vector4(0.204f, 0.102f, 0.0f, 1.0f), 1, false);

	mngr->addActor(_grp_BACKGROUND, stFg);
	mngr->addActor(_grp_BACKGROUND, stBg);
}