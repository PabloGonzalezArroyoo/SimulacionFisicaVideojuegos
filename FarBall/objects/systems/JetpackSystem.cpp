#include "JetpackSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../../RenderUtils.hpp"

void JetpackSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			break;
		case _m_UPDATE_FUEL:
			updateFuel(m.fuel_data.fuel);
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

	// Crear generador de part�culas que sigue al pinguino
	Particle* pt = new Particle(jetpack->getPos(), Vector3(0), TIME, colors[RED], CreateShape(PxSphereGeometry(3)), 10);
	pt->setLifeTime(1);
	partGen = new UniformGenerator("Pinguino", pt, jetpack->getPos(), Vector3(0), 0.5);
	pt->setInvisible();

	// Crear generadores de viento
	WindForceGenerator* wfgUp = new WindForceGenerator(jetpack->getPos(), Vector3(CONSTANT_X_VEL, 20, 0), 0, colors[RED], 1);
	WindForceGenerator* wfgDown = new WindForceGenerator(jetpack->getPos(), Vector3(CONSTANT_X_VEL, -20, 0), 0, colors[RED], 1);
	mngr->getForceRegistry()->addRegistry(wfgUp, jetpack);
	mngr->getForceRegistry()->addRegistry(wfgDown, jetpack);
	wfgUp->setActive(false);
	wfgDown->setActive(false);
	dirs.push_back(wfgUp);
	dirs.push_back(wfgDown);

	// A�adir objetos a la estructura
	mngr->addActor(_grp_GENERAL, base.first);
	mngr->addActor(_grp_GENERAL, base.second);
	mngr->addActor(_grp_GENERAL, jetpack);
	mngr->setHandler(_hdlr_JETPACK, jetpack);

	// Guardar la c�mara y posicionarla
	camera = GetCamera();
	camera->setView(jetpack->getPos() + Vector3(0.0, -20.0, -100.0), Vector3(0.0f, 0.0f, 1.0f));
}

void JetpackSystem::update(double t) {
	if (hit) {
		Vector3 jetPos = jetpack->getPos();
		// Generar part�culas
		list<Actor*> particles = partGen->generateParticles(t);
		partGen->getModel()->setPos(jetPos);
		for (Actor* a : particles) mngr->addActor(_grp_FOLLOW_PARTICLES, a);

		// Actualizar objetos
		for (Actor* a : mngr->getActors(_grp_GENERAL)) a->integrate(t);
		for (Actor* a : mngr->getActors(_grp_FOLLOW_PARTICLES)) {
			a->integrate(t);
			if (a->getPos().x < jetPos.x - 200) a->setAlive(false);
		}
		for (Actor* a : mngr->getActors(_grp_EXPLODE_PARTICLES)) {
			a->integrate(t);
			if (!a->getAlive()) mngr->getForceRegistry()->deleteActorRegistry(a);
		}

		// Actualizar c�mara
		camera->setView(Vector3(jetpack->getPos().x, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
	else jetpack->integrate(t);
}

void JetpackSystem::keyPressed(char key) {
	if (hit) {
		
		switch (key) {
			case 'I': useFuel(0); break;
			case 'K': useFuel(1); break;
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
			case 'K': dirs[1]->setActive(false); break;
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

void JetpackSystem::useFuel(int dir) {
	if (jetpack->getFuel() > 0) {
		jetpack->useFuel();
		dirs[dir]->setActive(true);

		createExplosion(jetpack->getPos(), 100, 10);

		Message m;
		m.id = _m_USE_FUEL;
		m.fuel_data.fuel = jetpack->getFuel();
		mngr->send(m);
	}
}

void JetpackSystem::updateFuel(int x) {
	jetpack->setFuel(jetpack->getFuel() + x);
	
	Message m;
	m.id = _m_USE_FUEL;
	m.fuel_data.fuel = jetpack->getFuel();
	mngr->send(m);
}

void JetpackSystem::createExplosion(Vector3 pos, int n, int rad) {
	// Crear generador
	ExplosionForceGenerator* efg = new ExplosionForceGenerator(pos, rad * 2000, 40000, 1);
	cout << pos.x << "\n";

	int a = 360 / n; float pi = 3.141516;
	for (int i = 0; i < n; i++) {
		float theta = rand() % 360;
		float phi = rand() % 360;

		float x = rad * sin(theta * pi / 180.0f) * cos(phi * pi / 180.0f);
		float y = rad * sin(theta * pi / 180.0f) * sin(phi * pi / 180.0f);
		float z = rad * cos(theta * pi / 180.0f);

		Particle* p;
		p = new Particle(pos + Vector3(x, y, z), Vector3(0), BOUNDARIES, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		p->setBoundaries(pos + Vector3(200, 200, 200));

		mngr->addActor(_grp_EXPLODE_PARTICLES, p);
		mngr->getForceRegistry()->addRegistry(efg, p);
	}
}