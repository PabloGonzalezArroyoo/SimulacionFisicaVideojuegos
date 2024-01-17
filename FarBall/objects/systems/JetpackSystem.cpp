#include "JetpackSystem.h"
#include "../../structure/ecs/Manager.h"
#include "../../RenderUtils.hpp"
#include "../../structure/states/GameState.h"

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

	// Crear generador de partículas que sigue al jetpack
	Particle* pt = new Particle(jetpack->getPos(), Vector3(0), TIME, colors[RED], CreateShape(PxSphereGeometry(3)), 10);
	pt->setLifeTime(1);
	partGen = new UniformGenerator("Jetpack", pt, jetpack->getPos(), Vector3(0), 0.5);
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
	// Si está el jetpack en el aire
	if (hit) {
		Vector3 jetPos = jetpack->getPos();

		// Generar partículas
		list<Actor*> particles = partGen->generateParticles(t);
		partGen->getModel()->setPos(jetPos);
		for (Actor* a : particles) mngr->addActor(_grp_FOLLOW_PARTICLES, a);

		// Actualizar objetos y borrar si procede
		for (Actor* a : mngr->getActors(_grp_GENERAL)) a->integrate(t);
		for (Actor* a : mngr->getActors(_grp_FOLLOW_PARTICLES)) {
			a->integrate(t);
			if (a->getPos().x < jetPos.x - 200) a->setAlive(false);
		}
		for (Actor* a : mngr->getActors(_grp_EXPLODE_PARTICLES)) {
			a->integrate(t);
			if (!a->getAlive()) mngr->getForceRegistry()->deleteActorRegistry(a);
		}

		// Actualizar cámara
		camera->setView(Vector3(jetpack->getPos().x, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
	else jetpack->integrate(t);

	// Comprobar si se choca contra el suelo
	if (jetpack->getPos().y < -43) {
		// Enviar caracter especial para terminar el estado
		mngr->getGameState()->keyPressed('@');
	}
}

void JetpackSystem::keyPressed(char key) {
	// Si estoy en el aire, solo puedo usar el jetpack
	if (hit) {
		switch (key) {
			// Usar el jetpack
			case 'I': useFuel(0); break;
			case 'K': useFuel(1); break;
			default: break;
		}
	}
	// Si no, solo puedo lanzarme
	else {
		switch (key) {
			case ' ':
				// Lanzar
				launch();
			break;
			default: break;
		}
	}
}

void JetpackSystem::keyReleased(char key) {
	// Si estoy en el aire
	if (hit) {
		switch (key) {
			// Descativar dirección cuando se deje de pulsar
			case 'I': dirs[0]->setActive(false); break;
			case 'K': dirs[1]->setActive(false); break;
			default: break;
		}
	}
}

// Lanzar al jetpack
void JetpackSystem::launch() {
	// Si estoy dentro de la zona de lanzamiento
	if (abs(jetpack->getPos().y - base.second->getPos().y) < 7) {
		// Marcar
		hit = true;

		// Borrar base
		base.first->setAlive(false);
		base.second->setAlive(false);

		// Lanzar
		jetpack->launch();

		// Actualizar posición de la cámara
		camera->setView(jetpack->getPos() + Vector3(0.0, 100.0, -200.0), Vector3(0.25f, -0.4f, 1.0f));
	}
}

// Usar combustible
void JetpackSystem::useFuel(int dir) {
	// Si tengo
	if (jetpack->getFuel() > 0) {
		// Usarlo
		jetpack->useFuel();
		dirs[dir]->setActive(true);

		// Crear explosión
		createExplosion(jetpack->getPos(), 20, 10);

		// Mandar mensaje de uso (para otros sistemas)
		Message m;
		m.id = _m_USE_FUEL;
		m.fuel_data.fuel = jetpack->getFuel();
		mngr->send(m);
	}
}

// Actualizar la cantidad de combustible
void JetpackSystem::updateFuel(int x) {
	// Actualizar
	jetpack->setFuel(jetpack->getFuel() + x);
	
	// Mandar mensaje de uso (para otros sistemas)
	Message m;
	m.id = _m_USE_FUEL;
	m.fuel_data.fuel = jetpack->getFuel();
	mngr->send(m);
}

void JetpackSystem::createExplosion(Vector3 pos, int n, int rad) {
	// Crear generador
	ExplosionForceGenerator* efg = new ExplosionForceGenerator(pos, rad * 20, 4000, 1);

	// Crear media esfera
	int a = 360 / n; float pi = 3.141516;
	for (int i = 0; i < n; i++) {
		float theta = rand() % 360;
		float phi = rand() % 180;

		float x = rad * sin(theta * pi / 180.0f) * cos(phi * pi / 180.0f);
		float y = rad * sin(theta * pi / 180.0f) * sin(phi * pi / 180.0f);
		float z = rad * cos(theta * pi / 180.0f);

		// Crear partícula con límites
		Particle* p;
		p = new Particle(pos + Vector3(x, y, z), Vector3(0), BOUNDARIES, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 9 + 1);
		p->setBoundaries(pos + Vector3(100, 100, 100));

		// Añadir a la estructura
		mngr->addActor(_grp_EXPLODE_PARTICLES, p);
		mngr->getForceRegistry()->addRegistry(efg, p);
	}
}