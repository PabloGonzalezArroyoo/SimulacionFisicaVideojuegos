#include "Rings.h"
#include "Jetpack.h"

Rings::Rings(Vector3 pos, Vector4 col, Manager* mg) : mng(mg) {

	Particle* ptUp = new Particle(pos + Vector3(0, 20, 0), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 3, 20)), 1);;
	Particle* ptDown = new Particle(pos + Vector3(0, -20, 0), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 3, 20)));;
	Particle* ptLeft = new Particle(pos + Vector3(0, 0, -20), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 20, 3)));;
	Particle* ptRight = new Particle(pos + Vector3(0, 0, 20), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 20, 3)));;
	
	parts.push_back(ptUp);
	parts.push_back(ptDown);
	parts.push_back(ptLeft);
	parts.push_back(ptRight);

	mng->addActor(_grp_GENERAL, ptUp);
	mng->addActor(_grp_GENERAL, ptDown);
	mng->addActor(_grp_GENERAL, ptLeft);
	mng->addActor(_grp_GENERAL, ptRight);

	int spring = rand() % 10;
	if (true) {
		spg = new AnchoredSpringForceGenerator(pos + Vector3(0, 60, 0), 1, 80);
		mng->getForceRegistry()->addRegistry(spg, ptUp);
		gfg = new GravityForceGenerator(Vector3(0, -9.8, 0));
		mng->getForceRegistry()->addRegistry(gfg, ptUp);
	}
}

Rings::~Rings() {
	for (int i = 0; i < parts.size(); i++) parts[i]->setAlive(false);
	mng->getForceRegistry()->deleteForceRegistry(spg);
	mng->getForceRegistry()->deleteForceRegistry(gfg);
	delete spg;
	delete gfg;
}

bool Rings::integrate(double t) {
	// Obtener posiciones
	Vector3 jetPos = mng->getHandler(_hdlr_JETPACK)->getPos();
	Vector3 ptUpPos = parts[0]->getPos();

	// Integrar
	parts[0]->integrate(t);

	// Mover todo el conjunto de partículas si está anclada a un spring
	if (spg != nullptr) {
		for (int i = 1; i < parts.size(); i++) {
			int y = ptUpPos.y - parts[0]->getPos().y;
			parts[i]->setPos(parts[i]->getPos() - Vector3(0, y, 0));
		}
	}

	// Comprobar si el jetpack pasa a través de él, mandando un mensaje en tal caso
	if (jetPos.x < ptUpPos.x + 1 && jetPos.x > ptUpPos.x - 1 && jetPos.y < ptUpPos.y + 5 && jetPos.y > ptUpPos.y - 50) {
		Message m;
		m.id = _m_UPDATE_FUEL;
		m.fuel_data.fuel = 10;
		mng->send(m);
		return false;
	}
	// O si se debe eliminar por quedarse atrás
	else if (jetPos.x > ptUpPos.x + 200) 
		return false;

	return true;
}