#include "Rings.h"
#include "Jetpack.h"

Rings::Rings(Vector3 pos, Vector4 col, Manager* mg) : mng(mg) {
	// Crear el anillo
	Particle* ptUp = new Particle(pos + Vector3(0, 20, 0), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 3, 20)), 1);;
	Particle* ptDown = new Particle(pos + Vector3(0, -20, 0), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 3, 20)));;
	Particle* ptLeft = new Particle(pos + Vector3(0, 0, -20), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 20, 3)));;
	Particle* ptRight = new Particle(pos + Vector3(0, 0, 20), Vector3(0), NONE, col, CreateShape(PxBoxGeometry(3, 20, 3)));;
	
	// Añadir a la estructura
	parts.push_back(ptUp);
	parts.push_back(ptDown);
	parts.push_back(ptLeft);
	parts.push_back(ptRight);
	mng->addActor(_grp_GENERAL, ptUp);
	mng->addActor(_grp_GENERAL, ptDown);
	mng->addActor(_grp_GENERAL, ptLeft);
	mng->addActor(_grp_GENERAL, ptRight);
}

Rings::~Rings() {
	// Matar partículas
	for (int i = 0; i < parts.size(); i++) parts[i]->setAlive(false);
}

bool Rings::integrate(double t) {
	// Obtener posiciones
	Vector3 jetPos = mng->getHandler(_hdlr_JETPACK)->getPos();
	Vector3 ptUpPos = parts[0]->getPos();

	// Integrar
	parts[0]->integrate(t);

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