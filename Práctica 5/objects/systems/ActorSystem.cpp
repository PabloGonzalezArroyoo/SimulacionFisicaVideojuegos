#include "ActorSystem.h"

ActorSystem::ActorSystem(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc) {
	floor = new RigidBody(ph, sc, new PxTransform(Vector3(-20)), CreateShape(PxBoxGeometry(400, 2, 400)), NONE,
		colors[BLUE], false);
}

ActorSystem::~ActorSystem() {
	// Borrar generadores
	for (ActorGenerator* p : _actor_generators) delete p;
	_actor_generators.clear();

	// Borrar partículas
	for (Actor* p : _actors) delete p;
	_actors.clear();

	// Borrar partículas no eliminadas
	for (int i = 0; i < _actorsToDelete.size(); i++) delete* _actorsToDelete[i];
	_actorsToDelete.clear();
}

void ActorSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (ActorGenerator* p : _actor_generators) {
		if (rigidLimit != -1 && rigidCounter < rigidLimit) {
			list<Actor*> rigids = p->generateParticles(t);
			if (!rigids.empty()) {
				rigidCounter += rigids.size();
				_actors.splice(_actors.end(), rigids);
			}
		}
	}
	
	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _actors.begin(); it != _actors.end(); it++) {
		if (!(*it)->integrate(t)) {
			_actorsToDelete.push_back(it);
			if (rigidLimit != -1) rigidCounter--;
		}
	}
	
	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _actorsToDelete.size(); i++) {
		Actor* p = *_actorsToDelete[i];
		_actors.erase(_actorsToDelete[i]);
		delete p;
	}
	_actorsToDelete.clear();
}

void ActorSystem::keyPress(char t) {
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

void ActorSystem::resetScene() {
	// Resetear contador
	if (rigidLimit != -1) rigidCounter = 0;

	// Borrar rígidos
	for (auto it = _actors.begin(); it != _actors.end(); it++) _actorsToDelete.push_back(it);

	// Borrar generadores
	for (auto it = _actor_generators.begin(); it != _actor_generators.end(); it++) {
		delete* it;
	}
	_actor_generators.clear();
}

void ActorSystem::createGaussian(bool st) {
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		TIME, colors[YELLOW]);
	rig->setLifeTime(10);

	st ? 
		_actor_generators.push_back(new GaussianGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20))) : 
		_actor_generators.push_back(new GaussianGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20), 0, false, Vector3(50)));
	
	rig->setInvisible();
}

void ActorSystem::createUniform(bool st) {
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		TIME, colors[YELLOW]);
	rig->setLifeTime(10);

	st ?
		_actor_generators.push_back(new UniformGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20))) :
		_actor_generators.push_back(new UniformGenerator("Rigid", rig, Vector3(0, 50, 0), Vector3(20), 0, false, Vector3(50)));

	rig->setInvisible();
}