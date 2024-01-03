#include "ActorSystem.h"

// Constructora
ActorSystem::ActorSystem(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc), state(A_NONE), rigidCounter(0){
	_forceRegistry = new ForceRegistry();
}

// Destructora
ActorSystem::~ActorSystem() {
	// Borrar generadores
	for (ActorGenerator* p : _actor_generators) delete p;
	_actor_generators.clear();

	// Borrar partículas
	for (Actor* p : _actors) delete p;
	_actors.clear();

	// Borrar registro
	if (_forceRegistry != nullptr) delete _forceRegistry;

	// Borrar generadores
	for (ForceGenerator* fg : _force_generators) delete fg;
	_force_generators.clear();

	// Borrar partículas no eliminadas
	for (int i = 0; i < _actorsToDelete.size(); i++) delete* _actorsToDelete[i];
	_actorsToDelete.clear();
}

// Actualizar
void ActorSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (ActorGenerator* p : _actor_generators) {
		if (rigidLimit == -1) {
			list<Actor*> rigids = p->generateParticles(t);
			if (!rigids.empty()) {
				if (state == A_TORNADO || state == A_WIND) attachForces(rigids);
				_actors.splice(_actors.end(), rigids);
			}
		}
		else if (rigidCounter < rigidLimit){
			list<Actor*> rigids = p->generateParticles(t);
			if (!rigids.empty()) {
				rigidCounter += rigids.size();
				if (state == A_TORNADO || state == A_WIND) attachForces(rigids);
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
	
	// Actualizar fuerzas
	if (_forceRegistry != nullptr) {
		_forceRegistry->updateForces();
		_forceRegistry->updateTime(t);
	}

	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _actorsToDelete.size(); i++) {
		Actor* p = *_actorsToDelete[i];
		if (_forceRegistry != nullptr) _forceRegistry->deleteActorRegistry(p);
		_actors.erase(_actorsToDelete[i]);
		delete p;
	}
	_actorsToDelete.clear();
}

// Procesar teclas
void ActorSystem::keyPress(char t) {
	switch (t)
	{
		default: break;
	}
}

// Adjuntar fuerzas
void ActorSystem::attachForces(list<Actor*>& l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		_forceRegistry->addRegistry(*_force_generators.begin(), *it);
	}
}

// Resetear la escena
void ActorSystem::resetScene() {
	// Resetear contador
	if (rigidLimit != -1) rigidCounter = 0;

	// Borrar rígidos
	for (auto it = _actors.begin(); it != _actors.end(); it++) {
			Actor* p = *it;
			if (_forceRegistry != nullptr) _forceRegistry->deleteActorRegistry(p);
			delete p;
	}
	_actors.clear();
	_actorsToDelete.clear();

	// Borrar generadores de actores
	for (auto it = _actor_generators.begin(); it != _actor_generators.end(); it++) delete* it;
	_actor_generators.clear();

	// Borrar generadores de fuerzas
	if (!_force_generators.empty()) {
		for (auto it = _force_generators.begin(); it != _force_generators.end(); it++) {
			delete* it;
			_forceRegistry->deleteForceRegistry(*it);
		}
		_force_generators.clear();
	}
}

// Obtener un generador por su nombre
ForceGenerator* ActorSystem::getGenerator(string name) {
	auto it = _force_generators.begin();
	bool enc = false;
	while (!enc && it != _force_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return enc ? (*it) : nullptr;
}