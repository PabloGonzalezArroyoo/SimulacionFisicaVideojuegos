#include "FireworkSystem.h"
#include "../../structure/ecs/Manager.h"

void FireworkSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_INIT_STATE:
		state = m.state_data.st;
		points = m.state_data.points;
		break;
	}
}

void FireworkSystem::initSystem() {
	// Posicionar cámara
	GetCamera()->setView(Vector3(0, 20, -100), Vector3(0.0f, 0.2f, 1.0f));

	// Primer generador
	Particle* pt = new Particle(Vector3(0), Vector3(80), TIME, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)));
	pt->setLifeTime(1);
	Firework* model = new Firework(pt, nullptr, 4, { 3, 4 });
	fireworks.first = new FireworkGenerator("fire1", model, Vector3(0, 0, -100), Vector3(30, 25, 30));

	//// Segundo generador
	//pt = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
	//pt->setLifeTime(1);
	//model = new Firework(pt, nullptr, 3, { 3, 5 });
	//fireworks.second = new FireworkGenerator("fire2", model, Vector3(-50, 0, -100), Vector3(30, 25, 30));

	// Generador de gravedad
	gfg = new GravityForceGenerator(Vector3(0, -9.8, 0));
}

void FireworkSystem::update(double t) {
	// Generar partículas
	list<Actor*> particles = fireworks.first->generateParticles(t);
	for (Actor* a : particles) {
		mngr->addActor(_grp_FIREWORKS, a);
		mngr->getForceRegistry()->addRegistry(gfg, a);
	}

	// Actualización y explosión
	cout << mngr->getActors(_grp_FIREWORKS).size() << "\n";
	for (Actor* a : mngr->getActors(_grp_FIREWORKS)) {
		a->integrate(t);
		//cout << a->getPos().y << "\n";
		if (!a->getAlive()) {
			cout << "hola" << "\n";
			mngr->getForceRegistry()->deleteActorRegistry(a);
			list<Actor*> expParts = static_cast<Firework*>(a)->explode();
			for (Actor* a : expParts) {
				mngr->addActor(_grp_FIREWORKS, a);
				mngr->getForceRegistry()->addRegistry(gfg, a);
			}
		}
	}
}