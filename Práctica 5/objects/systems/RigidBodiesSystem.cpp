#include "RigidBodiesSystem.h"

RigidBodiesSystem::RigidBodiesSystem(PxPhysics* gPhysics, PxScene* gScene) {
	RigidBody* floor = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(-20)),
		CreateShape(PxBoxGeometry(400, 2, 400)), R_NONE, rColors[R_BLUE], false);
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), R_NONE, rColors[R_YELLOW]);
	_rigid_generators.push_back(new GaussianRigidGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20)));
}

RigidBodiesSystem::~RigidBodiesSystem() {

}

void RigidBodiesSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (RigidGenerator* p : _rigid_generators) {
		list<RigidBody*> rigids = p->generateParticles(t);
		if (!rigids.empty()) _rigidBodies.splice(_rigidBodies.end(), rigids);
	}
	
	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _rigidBodies.begin(); it != _rigidBodies.end(); it++) {
		if (!(*it)->integrate(t)) _rigidsToDelete.push_back(it);
	}
	
	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _rigidsToDelete.size(); i++) {
		RigidBody* p = *_rigidsToDelete[i];
		delete p;
	}
	_rigidsToDelete.clear();
}

void RigidBodiesSystem::keyPress(char t) {

}