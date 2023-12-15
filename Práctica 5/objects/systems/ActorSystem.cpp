#include "ActorSystem.h"

ActorSystem::ActorSystem(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc), state(A_NONE), rigidCounter(0){
	addFloor();
	_forceRegistry = new ForceRegistry();
}

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
	_forceRegistry->updateForces();
	_forceRegistry->updateTime(t);

	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _actorsToDelete.size(); i++) {
		Actor* p = *_actorsToDelete[i];
		_forceRegistry->deleteActorRegistry(p);
		_actors.erase(_actorsToDelete[i]);
		delete p;
	}
	_actorsToDelete.clear();
}

void ActorSystem::keyPress(char t) {
	switch (t)
	{
		case 'R':
			resetScene();
			state = A_GRAVITY;
			createGravity(30, 30);
		break;
		case 'G': 
			resetScene();
			state = A_GAUSSIAN;
			createGaussian(true); 
			break;
		case 'H': 
			resetScene();
			state = A_GAUSSIAN;
			createGaussian(false); 
			break;
		case 'U':
			resetScene();
			state = A_UNIFORM;
			createUniform(true);
			break;
		case 'I':
			resetScene();
			state = A_UNIFORM;
			createUniform(false);
			break;
		case 'Q':
			state = A_WIND;
			createWind();
			break;
		case 'T':
			resetScene();
			state = A_TORNADO;
			createTornado();
			break;
		case 'E':
			if (state != A_EXPLOSION) resetScene();
			createExplosion(100, 40, state);
			state == A_EXPLOSION ? state = A_NONE : state = A_EXPLOSION;
			break;
		default: break;
	}
}

void ActorSystem::attachForces(list<Actor*>& l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		_forceRegistry->addRegistry(*_force_generators.begin(), *it);
	}
}

void ActorSystem::resetScene() {
	// Resetear contador
	if (rigidLimit != -1) rigidCounter = 0;

	// Borrar rígidos
	for (auto it = _actors.begin(); it != _actors.end(); it++) _actorsToDelete.push_back(it);

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

void ActorSystem::createGravity(int acts, int rad) {
	addFloor();
	float pi = 3.141516;
	for (int i = 0; i < acts; i++) {
		float angle = (i * 2 * pi) / acts;
		float x = std::cos(angle) * rad;
		float y = std::sin(angle) * rad;
		RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(x, 30, y)), CreateShape(PxBoxGeometry(2, 2, 2)),
			NONE, colors[YELLOW]);
		_actors.push_back(rig);
	}
}

void ActorSystem::createGaussian(bool st, Vector3 pos, Vector3 var, float spTime, Vector3 offset) {
	addFloor();
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		BOUNDARIES, colors[YELLOW]);
	
	st ? rig->setBoundaries(Vector3(600)) : rig->setBoundaries(Vector3(200));

	st ? 
		_actor_generators.push_back(new GaussianGenerator("Rigid", rig, Vector3(pos), Vector3(var), spTime)) : 
		_actor_generators.push_back(new GaussianGenerator("Rigid", rig, Vector3(pos), Vector3(var), spTime,
			false, Vector3(offset)));
	
	rig->setInvisible();
}

void ActorSystem::createUniform(bool st, Vector3 pos, Vector3 var, float spTime, Vector3 offset) {
	addFloor();
	RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		BOUNDARIES, colors[YELLOW]);
	
	st ? rig->setBoundaries(Vector3(600)) : rig->setBoundaries(Vector3(200));

	st ?
		_actor_generators.push_back(new UniformGenerator("Rigid", rig, Vector3(pos), Vector3(var), spTime)) :
		_actor_generators.push_back(new UniformGenerator("Rigid", rig, Vector3(pos), Vector3(var), spTime,
			false, Vector3(offset)));

	rig->setInvisible();
}

void ActorSystem::createWind() {
	addFloor();
	ForceGenerator* fg = getGenerator("wind");
	if (fg == nullptr) {
		resetScene();

		//RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0)), CreateShape(PxBoxGeometry(2, 2, 2)),
		//	NONE, colors[YELLOW]);
		//rig->setMass(10);
		//_actors.push_back(rig);

		createUniform(false);

		WindForceGenerator* wfg = new WindForceGenerator(Vector3(0, -10, 0), Vector3(50, 80, 0), 100, colors[GREEN], 1, true);
		_force_generators.push_back(wfg);

		//_forceRegistry->addRegistry(wfg, rig);
	}
	else fg->setActive(!fg->getActive());
}

void ActorSystem::createTornado() {
	createUniform(false, Vector3(10, -30, 10), Vector3(0, 10, 0), 0, Vector3(20));
	deleteFloor();

	TornadoForceGenerator* tfg = new TornadoForceGenerator(Vector3(0), 200, 1);
	_force_generators.push_back(tfg);
}

// Crea rigidos en torno a una esfera
void ActorSystem::createSphere(int acts, int rad) {
	int a = 360 / acts; float pi = 3.141516;
	for (int i = 0; i < acts; i++) {
		float theta = rand() % 360;
		float phi = rand() % 360;

		float x = rad * sin(theta * pi / 180.0f) * cos(phi * pi / 180.0f);
		float y = rad * sin(theta * pi / 180.0f) * sin(phi * pi / 180.0f);
		float z = rad * cos(theta * pi / 180.0f);

		RigidBody* rig = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(x, y + 30, z)),
			CreateShape(PxBoxGeometry(2, 2, 2)), BOUNDARIES, colors[YELLOW]);
		rig->setBoundaries(Vector3(800));
		_actors.push_back(rig);
	}
}

void ActorSystem::createExplosion(int acts, int rad, State st) {
	if (state != A_EXPLOSION) createSphere(acts, rad);
	else {
		ExplosionForceGenerator* efg = new ExplosionForceGenerator(Vector3(0), 100, 400000, 0.1);
		_force_generators.push_back(efg);
		attachForces(_actors);
	}
}

ForceGenerator* ActorSystem::getGenerator(string name) {
	auto it = _force_generators.begin();
	bool enc = false;
	while (!enc && it != _force_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return enc ? (*it) : nullptr;
}