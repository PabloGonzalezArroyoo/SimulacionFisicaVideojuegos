#include "RigidBodiesSystem.h"

RigidBodiesSystem::RigidBodiesSystem(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc) {
	floor = new RigidBody(ph, sc, new PxTransform(Vector3(-20)), CreateShape(PxBoxGeometry(400, 2, 400)), NONE,
		colors[BLUE], false);
}

RigidBodiesSystem::~RigidBodiesSystem() {
	// Borrar generadores
	for (RigidGenerator* p : _rigid_generators) delete p;
	_rigid_generators.clear();

	// Borrar partículas
	for (RigidBody* p : _rigidBodies) delete p;
	_rigidBodies.clear();

	// Borrar partículas no eliminadas
	for (int i = 0; i < _rigidsToDelete.size(); i++) delete* _rigidsToDelete[i];
	_rigidsToDelete.clear();
}

void RigidBodiesSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (RigidGenerator* p : _rigid_generators) {
		if (rigidLimit != -1 && rigidCounter < rigidLimit) {
			list<RigidBody*> rigids = p->generateParticles(t);
			if (!rigids.empty()) {
				rigidCounter += rigids.size();
				_rigidBodies.splice(_rigidBodies.end(), rigids);
			}
		}
	}
	
	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _rigidBodies.begin(); it != _rigidBodies.end(); it++) {
		if (!(*it)->integrate(t)) {
			_rigidsToDelete.push_back(it);
			if (rigidLimit != -1) rigidCounter--;
		}
	}
	
	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _rigidsToDelete.size(); i++) {
		RigidBody* p = *_rigidsToDelete[i];
		_rigidBodies.erase(_rigidsToDelete[i]);
		delete p;
	}
	_rigidsToDelete.clear();
}

void RigidBodiesSystem::keyPress(char t) {
	switch (t)
	{
		case 'G': 
			resetScene();
			createGaussian(true); 
			break;
		case 'H': 
			resetScene();
			createGaussian(false); 
			break;
		case 'U':
			resetScene();
			createUniform(true);
			break;
		case 'I':
			resetScene();
			createUniform(false);
			break;
		default: break;
	}
}

void RigidBodiesSystem::resetScene() {
	// Resetear contador
	if (rigidLimit != -1) rigidCounter = 0;

	// Borrar rígidos
	for (auto it = _rigidBodies.begin(); it != _rigidBodies.end(); it++) _rigidsToDelete.push_back(it);

	// Borrar generadores
	for (auto it = _rigid_generators.begin(); it != _rigid_generators.end(); it++) {
		delete* it;
	}
	_rigid_generators.clear();
}

void RigidBodiesSystem::createGaussian(bool st) {
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		TIME, colors[YELLOW]);
	rig->setLifeTime(10);

	st ? 
		_rigid_generators.push_back(new GaussianRigidGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20))) : 
		_rigid_generators.push_back(new GaussianRigidGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20), 0, false, Vector3(50)));
	
	rig->setInvisible();
}

void RigidBodiesSystem::createUniform(bool st) {
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		TIME, colors[YELLOW]);
	rig->setLifeTime(10);

	st ?
		_rigid_generators.push_back(new UniformRigidGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20))) :
		_rigid_generators.push_back(new UniformRigidGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20), 0, false, Vector3(50)));

	rig->setInvisible();
}