#include "JetpackSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../../RenderUtils.hpp"

void JetpackSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			break;
	}
}

void JetpackSystem::initSystem() {
	// Crear pinguino
	jetpack = new Jetpack(mngr->getPhysics(), mngr->getScene(), PxTransform(Vector3(0)),
		CreateShape(PxBoxGeometry(5, 5, 5)), NONE, Vector4(1, 1, 1, 1), 10);
	jetpack->getDynRigid()->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// Crear base
	base = {
		new Particle(Vector3(0, -47.5, 0), Vector3(0), NONE, Vector4(0.71, 0.71, 0.107, 1),
		CreateShape(PxBoxGeometry(20, 0.1, 20))),
		new Particle(Vector3(0, -20, 0), Vector3(0), NONE, Vector4(0.5, 1.0, 0.5, 1),
		CreateShape(PxBoxGeometry(10, 2, 10)))
	};

	// Crear generador de partículas que sigue al pinguino
	Particle* pt = new Particle(jetpack->getPos(), Vector3(0), TIME, colors[RED], CreateShape(PxSphereGeometry(3)), 10);
	pt->setLifeTime(1);
	partGen = new UniformGenerator("Pinguino", pt, jetpack->getPos(), Vector3(0), 0.5);
	pt->setInvisible();

	// Crear generadores de viento
	WindForceGenerator* wfgUp = new WindForceGenerator(jetpack->getPos(), Vector3(0, 10, 0), 0, colors[RED], 10);
	mngr->getForceRegistry()->addRegistry(wfgUp, jetpack);
	wfgUp->setActive(false);
	dirs.push_back(wfgUp);

	// Añadir objetos a la estructura
	mngr->addActor(_grp_GENERAL, base.first);
	mngr->addActor(_grp_GENERAL, base.second);
	mngr->addActor(_grp_GENERAL, jetpack);
	mngr->setHandler(_hdlr_JETPACK, jetpack);

	// Guardar la cámara y posicionarla
	camera = GetCamera();
	camera->setView(jetpack->getPos() + Vector3(0.0, -20.0, -100.0), Vector3(0.0f, 0.0f, 1.0f));
}

void JetpackSystem::update(double t) {
	if (hit) {
		// Generar partículas
		list<Actor*> particles = partGen->generateParticles(t);
		partGen->getModel()->setPos(jetpack->getPos());
		for (Actor* a : particles) mngr->addActor(_grp_PARTICLES, a);

		// Actualizar objetos
		for (Actor* a : mngr->getActors(_grp_PARTICLES)) a->integrate(t);
		for (Actor* a : mngr->getActors(_grp_GENERAL)) a->integrate(t);

		// Actualizar cámara
		camera->setView(Vector3(jetpack->getPos().x, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
	else jetpack->integrate(t);
}

void JetpackSystem::keyPressed(char key) {
	if (hit) {
		Message m;
		switch (key) {
			case 'I':
				if (jetpack->getFuel() > 0) {
					jetpack->useFuel();
					dirs[0]->setActive(true);
					m.id = _m_USE_FUEL;
					m.fuel_data.fuel = jetpack->getFuel();
					mngr->send(m);
				}
				break;
			default: break;
		}
	}
	else {
		switch (key) {
			case ' ':
				if (!hit) launch();
			break;
			default: break;
		}
	}
}

void JetpackSystem::keyReleased(char key) {
	if (hit) {
		switch (key) {
			case 'I': dirs[0]->setActive(false); break;
			default: break;
		}
	}
}

void JetpackSystem::launch() {
	if (abs(jetpack->getPos().y - base.second->getPos().y) < 7) {
		hit = true;
		base.first->setAlive(false);
		base.second->setAlive(false);
		jetpack->launch();
		camera->setView(jetpack->getPos() + Vector3(0.0, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
}