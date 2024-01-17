#include "FireworkSystem.h"
#include "../../structure/ecs/Manager.h"

void FireworkSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_INIT_STATE:
		state = m.state_data.st;
		break;
	}
}

void FireworkSystem::initSystem() {
	// Posicionar cámara
	GetCamera()->setView(Vector3(0, 20, -100), Vector3(0.0f, 0.2f, 1.0f));

	// Primer generador
	Particle* pt = new Particle(Vector3(0), Vector3(0, 200, 0), TIME, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)));
	pt->setLifeTime(1);
	Firework* model = new Firework(pt, nullptr, 4, { 3, 4 });
	pt->setInvisible();
	fireworks.first = new FireworkGenerator("fire1", model, Vector3(20, 0, 0), Vector3(20, 100, 20));
	mngr->addActor(_grp_GENERAL, pt);
	mngr->addActor(_grp_GENERAL, model);

	//// Segundo generador
	pt = new Particle(Vector3(0), Vector3(0, 200, 0), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
	pt->setLifeTime(1);
	model = new Firework(pt, nullptr, 3, { 3, 5 });
	pt->setInvisible();
	fireworks.second = new FireworkGenerator("fire2", model, Vector3(-20, 0, 0), Vector3(20, 100, 20));
	mngr->addActor(_grp_GENERAL, model);

	// Generador de gravedad
	//gfg = new GravityForceGenerator(Vector3(0, -9.8, 0));
}

void FireworkSystem::update(double t) {
	// Generar partículas de ambos generadores
	list<Actor*> particlesFirst = fireworks.first->generateParticles(t);
	for (Actor* a : particlesFirst) {
		mngr->addActor(_grp_FIREWORKS, a);
		//mngr->getForceRegistry()->addRegistry(gfg, a);
	}
	list<Actor*> particlesSecond = fireworks.second->generateParticles(t);
	for (Actor* a : particlesSecond) {
		mngr->addActor(_grp_FIREWORKS, a);
		//mngr->getForceRegistry()->addRegistry(gfg, a);
	}

	// Actualización y explosión
	for (Actor* a : mngr->getActors(_grp_FIREWORKS)) {
		a->integrate(t);
		if (!a->getAlive()) {
			//mngr->getForceRegistry()->deleteActorRegistry(a);
			list<Actor*> expParts = static_cast<Firework*>(a)->explode();
			for (Actor* a : expParts) {
				mngr->addActor(_grp_FIREWORKS, a);
				//mngr->getForceRegistry()->addRegistry(gfg, a);
			}
		}
	}
}