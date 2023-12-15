#include "ActorSystem.h"

// Constructora
ActorSystem::ActorSystem(PxPhysics* ph, PxScene* sc) : gPhysics(ph), gScene(sc), state(A_NONE), rigidCounter(0){
	addFloor();
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

// Procesar teclas
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
		case 'Z':
			resetScene();
			state = A_ANCHORED;
			createAnchored();
			break;
		case 'X':
			resetScene();
			state = A_SPRING;
			createSpring(false);
			break;
		case 'C':
			resetScene();
			state = A_SLINKY;
			createSlinky();
			break;
		case 'V':
			resetScene();
			state = A_BOUYANCY;
			createBuoyancy();
			break;
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

// Crear prueba de gravedad
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

// Crear prueba de generador gausiano
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

// Crear prueba de generador uniforme
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

// Crear prueba de viento
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

// Crear prueba de tornado
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

// Crear prueba de explosion
void ActorSystem::createExplosion(int acts, int rad, State st) {
	if (state != A_EXPLOSION) createSphere(acts, rad);
	else {
		ExplosionForceGenerator* efg = new ExplosionForceGenerator(Vector3(0), 100, 400000, 0.1);
		_force_generators.push_back(efg);
		attachForces(_actors);
	}
}

void ActorSystem::createAnchored() {
	deleteFloor();
	RigidBody* rb1 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0, 45, 0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[YELLOW]);
	RigidBody* rb2 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0, 45, 5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[GREEN]);
	RigidBody* rb3 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0, 45, -5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[RED]);
	_actors.push_back(rb1);
	_actors.push_back(rb2);
	_actors.push_back(rb3);

	// Generadores
	AnchoredSpringForceGenerator* spg = new AnchoredSpringForceGenerator(Vector3(0, 50, 0), 4, 20);
	WindForceGenerator* wfg = new WindForceGenerator(Vector3(0), Vector3(10), 400, colors[GREEN], 10);
	_force_generators.push_back(spg);
	_force_generators.push_back(wfg);

	// Añadir a la estructura
	_forceRegistry->addRegistry(wfg, rb1);
	_forceRegistry->addRegistry(wfg, rb2);
	_forceRegistry->addRegistry(wfg, rb3);
	_forceRegistry->addRegistry(spg, rb1);
	_forceRegistry->addRegistry(spg, rb2);
	_forceRegistry->addRegistry(spg, rb3);
}

void ActorSystem::createSpring(bool el) {
	deleteFloor();
	RigidBody* rb1 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3( 50, 25, 0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[YELLOW]);
	RigidBody* rb2 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(-50, 25, 5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[GREEN]);
	RigidBody* rb3 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(  0, 50, -5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[RED]);
	RigidBody* rb4 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(  0, 0,  -5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[RED]);
	_actors.push_back(rb1);
	_actors.push_back(rb2);
	_actors.push_back(rb3);
	_actors.push_back(rb4);

	// Generadores
	SpringForceGenerator* sfg1 = new SpringForceGenerator(Vector3(0, 25, 0), 4, 10, rb2, el);
	SpringForceGenerator* sfg2 = new SpringForceGenerator(Vector3(0, 25, 0), 4, 10, rb1, el);
	SpringForceGenerator* sfg3 = new SpringForceGenerator(Vector3(0, 25, 0), 4, 10, rb4, el);
	SpringForceGenerator* sfg4 = new SpringForceGenerator(Vector3(0, 25, 0), 4, 10, rb3, el);

	// Añadir a la estructura
	_forceRegistry->addRegistry(sfg1, rb1);
	_forceRegistry->addRegistry(sfg2, rb2);
	_forceRegistry->addRegistry(sfg3, rb3);
	_forceRegistry->addRegistry(sfg4, rb4);

	_force_generators.push_back(sfg1);
	_force_generators.push_back(sfg2);
	_force_generators.push_back(sfg3);
	_force_generators.push_back(sfg4);
}

void ActorSystem::createSlinky() {
	deleteFloor();
	RigidBody* rb1 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(50, 25, 0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[YELLOW]);
	RigidBody* rb2 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(-50, 25, 5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[GREEN]);
	RigidBody* rb3 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0, 50, -5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[RED]);
	RigidBody* rb4 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(0, 0, -5)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[RED]);
	_actors.push_back(rb1);
	_actors.push_back(rb2);
	_actors.push_back(rb3);
	_actors.push_back(rb4);

	// Generadores de muelles
	AnchoredSpringForceGenerator* spg = new AnchoredSpringForceGenerator(Vector3(0, 150, 0), 4, 20);
	SpringForceGenerator* sfg1_2 = new SpringForceGenerator(Vector3(0), 4, 20, rb2);
	SpringForceGenerator* sfg2_1 = new SpringForceGenerator(Vector3(0), 4, 20, rb1);
	SpringForceGenerator* sfg2_3 = new SpringForceGenerator(Vector3(0), 4, 20, rb3);
	SpringForceGenerator* sfg3_2 = new SpringForceGenerator(Vector3(0), 4, 20, rb2);
	SpringForceGenerator* sfg3_4 = new SpringForceGenerator(Vector3(0), 4, 20, rb4);
	SpringForceGenerator* sfg4_3 = new SpringForceGenerator(Vector3(0), 4, 20, rb3);

	// Conectar muelles
	_forceRegistry->addRegistry(spg,	rb1);
	_forceRegistry->addRegistry(sfg1_2, rb1);
	_forceRegistry->addRegistry(sfg2_1, rb2);
	_forceRegistry->addRegistry(sfg2_3, rb2);
	_forceRegistry->addRegistry(sfg3_2, rb3);
	_forceRegistry->addRegistry(sfg3_4, rb3);
	_forceRegistry->addRegistry(sfg4_3, rb4);

	// Añadir a la estructura
	_force_generators.push_back(spg);
	_force_generators.push_back(sfg1_2);
	_force_generators.push_back(sfg2_1);
	_force_generators.push_back(sfg2_3);
	_force_generators.push_back(sfg3_2);
	_force_generators.push_back(sfg3_4);
	_force_generators.push_back(sfg4_3);
}

void ActorSystem::createBuoyancy() {
	deleteFloor();
	RigidBody* rb1 = new RigidBody(gPhysics, gScene, new PxTransform(Vector3(50, 25, 0)),
		CreateShape(PxBoxGeometry(2, 2, 2)), NONE, colors[YELLOW]);
	_actors.push_back(rb1);

	// Generador
	BuoyancyForceGenerator* bfg = new BuoyancyForceGenerator(Vector3(0), 3, 27, 50);

	// Añadir flotación
	_forceRegistry->addRegistry(bfg, rb1);

	// Añadir a la estructura
	_force_generators.push_back(bfg);
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