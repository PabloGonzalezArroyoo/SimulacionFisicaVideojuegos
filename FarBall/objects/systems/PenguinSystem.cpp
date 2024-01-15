#include "PenguinSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../../RenderUtils.hpp"

void PenguinSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			break;
	}
}

void PenguinSystem::initSystem() {
	// Crear pinguino
	penguin = new Penguin(mngr->getPhysics(), mngr->getScene(), PxTransform(Vector3(0)),
		CreateShape(PxBoxGeometry(5, 5, 5)), NONE, Vector4(1, 1, 1, 1), 10);
	penguin->getDynRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_LINEAR_Z |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// Crear base y bate
	base = new Particle(Vector3(0, -47.5, 0), Vector3(0), NONE, Vector4(0.71, 0.71, 0.107, 1),
		CreateShape(PxBoxGeometry(20, 0.1, 20)));
	bat = new Particle(Vector3(0, -20, 0), Vector3(0), NONE, Vector4(0.5, 1.0, 0.5, 1),
		CreateShape(PxBoxGeometry(10, 2, 10)));

	// Crear generador de partículas que sigue al pinguino
	Particle* pt = new Particle(penguin->getPos(), Vector3(0), TIME, colors[RED], CreateShape(PxSphereGeometry(3)), 10);
	pt->setLifeTime(1);
	partGen = new UniformGenerator("Pinguino", pt, penguin->getPos(), Vector3(0), 0.5);
	pt->setInvisible();

	// Añadir pinguino
	mngr->addActor(_grp_GENERAL, penguin);
	mngr->setHandler(_hdlr_PENGUIN, penguin);

	// Guardar la cámara y posicionarla
	camera = GetCamera();
	camera->setView(penguin->getPos() + Vector3(0.0, -20.0, -100.0), Vector3(0.0f, 0.0f, 1.0f));

	updatePos = 0;
}

void PenguinSystem::update(double t) {
	// Actualizar posición
	penguin->integrate(t);

	if (hit) {
		// Actualizar generadores
		list<Actor*> particles = partGen->generateParticles(t);
		partGen->getModel()->setPos(penguin->getPos());
		for (Actor* a : particles) mngr->addActor(_grp_PARTICLES, a);

		for (Actor* a : mngr->getActors(_grp_PARTICLES)) a->integrate(t);

		// Actualizar cámara
		camera->setView(Vector3(penguin->getPos().x, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
}

void PenguinSystem::keyPressed(char key) {
	if (hit) penguin->keyPressed(key);
	else {
		switch (key) {
			case ' ':
				if (!hit) launch();
			break;
			default: break;
		}
	}
}

void PenguinSystem::launch() {
	if (abs(penguin->getPos().y - bat->getPos().y) < 7) {
		hit = true;
		penguin->launch();
		camera->setView(penguin->getPos() + Vector3(0.0, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
}