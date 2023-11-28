#include "ParticleSystem.h"

// Constructora
ParticleSystem::ParticleSystem() {
	srand((unsigned int)time);

	if (practiceType == PARTICLES_P2A1) {
		#pragma region Particulas (Pr�ctica 2 - Actividad 1)
		// Generador de part�culas amarillas redondas
		Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
		//model->setBoundaries(Vector3(100));
		ParticleGenerator* ptGen = new GaussianParticleGenerator("Gaussian", model, model->getPos(), Vector3(35), 0);
		_particle_generators.push_back(ptGen);

		// Generador de part�culas azules cuadradas
		model = new Particle(Vector3(0), Vector3(50), TIME, colors[BLUE], CreateShape(PxBoxGeometry(2, 2, 2)));
		//model->setBoundaries(Vector3(200));
		ptGen = new UniformParticleGenerator("Uniform", model, model->getPos() + Vector3(-100, 0, 0), Vector3(35), 0);
		_particle_generators.push_back(ptGen);

		// Generador no est�tico
		//Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[BLUE], CreateShape(PxBoxGeometry(2, 2, 2)));
		////model->setBoundaries(Vector3(200));
		//ParticleGenerator*  ptGen = new UniformParticleGenerator("Uniform", model, model->getPos() + Vector3(-100, 0, 0), Vector3(35), 0, false, Vector3(20));
		//_particle_generators.push_back(ptGen);	
		#pragma endregion
	}	

	else if (practiceType == FIREWORKS_P2A2) {
		#pragma region Fireworks (Pr�ctica 2 - Actividad 2)
		// Generador de fireworks amarillos
		Particle* pt = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
		pt->setLifeTime(2);
		Firework* model = new Firework(pt, nullptr, 3, make_pair(3, 5)); // true para cambiar colores, false predeterminado
		pt->setInvisible();
		ParticleGenerator* ptGen = new FireworkGenerator("FireworksY1", model, Vector3(0), Vector3(15, 10, 15));
		_particle_generators.push_back(ptGen);

		// Generador de fireworks azules
		pt = new Particle(Vector3(0), Vector3(80), TIME, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)));
		pt->setLifeTime(2);
		model = new Firework(pt, nullptr, 4, make_pair(5, 8));
		pt->setInvisible();
		ptGen = new FireworkGenerator("FireworksB1", model, Vector3(-100, 0, -100), Vector3(30, 25, 30));
		_particle_generators.push_back(ptGen);

		//// Generador de fireworks verdes
		//pt = new Particle(Vector3(0), Vector3(100), TIME, colors[GREEN], CreateShape(PxBoxGeometry(2, 2, 2)));
		//pt->setLifeTime(2);
		//model = new Firework(pt, nullptr, 5, make_pair(8, 10));
		//pt->setInvisible(); 
		//ptGen = new FireworkGenerator("Fireworks", model, Vector3(-200, 0, -200), Vector3(40, 30, 40));
		//_particle_generators.push_back(ptGen);
		#pragma endregion
	}

	else if (practiceType == FORCES_P3) {
		#pragma region Fuerzas (Pr�ctica 3)
		// Contenedor de fuerzas y fuerzas
		_forceRegistry = new ParticleForceRegistry();
		createForces();

		if (particlesType == GeneratorsType) {
			// Generador de part�culas amarillas redondas
			if (forcesType != EXPLOSION) createWindOrTornadoParticles();
			else createParticleSpheres(1500, 10);
		}
		else if (particlesType == FireworksType) {
			// Generador de fireworks azules
			Particle* pt = new Particle(Vector3(0), Vector3(60), TIME, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)));
			pt->setLifeTime(2);
			Particle* model = new Firework(pt, nullptr, 4, make_pair(5, 8));
			pt->setInvisible();
			ParticleGenerator* ptGen = new FireworkGenerator("FireworksB1", model, Vector3(-100, 0, -100), Vector3(30, 25, 30));
			_particle_generators.push_back(ptGen);
		}
		#pragma endregion
	}

	else if (practiceType == SPRINGS_P4) {
		#pragma region Muelles (Pr�ctica 4)
		// Registro
		_forceRegistry = new ParticleForceRegistry();

		// Generadores b�sicos
		GravityForceGenerator* gfc = new GravityForceGenerator(Vector3(0, -10, 0));
		WindForceGenerator* wfg = new WindForceGenerator(Vector3(0), Vector3(100, 0, 0), 400, colors[GREEN], 20); wfg->setActive(false);
		
		// Part�cula
		Particle* pt1 = new Particle(Vector3(0, 50, 0), Vector3(0), NONE, colors[YELLOW], CreateShape(PxSphereGeometry(3)), 60);

		// A�adir registros, generadores y part�cula a la estructura
		_forceRegistry->addRegistry(gfc, pt1);
		_forceRegistry->addRegistry(wfg, pt1);
		_forceGenerators.push_back(gfc);
		_forceGenerators.push_back(wfg);
		_particles.push_back(pt1);

		if (springType == STATIC_SPRING) {
			// Generador de muelle est�tico
			AnchoredSpringForceGenerator* spg = new AnchoredSpringForceGenerator(Vector3(0), 20, 10);
			_forceRegistry->addRegistry(spg, pt1);
			_forceRegistry->addRegistry(gfc, pt1);
			_forceGenerators.push_back(spg);
		}
		else if (springType == PARTICLES_SPRING) {
			// Desactivar gravedad
			gfc->setActive(false);

			// Part�cula
			pt1->setPos(Vector3(100, 50, 0));
			Particle* pt2 = new Particle(Vector3(0, 50, 100), Vector3(0), NONE, colors[RED], CreateShape(PxSphereGeometry(3)), 60);

			// Generadores
			SpringForceGenerator* sfg1 = new SpringForceGenerator(Vector3(0), 20, 10, pt2);
			SpringForceGenerator* sfg2 = new SpringForceGenerator(Vector3(0), 20, 10, pt1);
			
			// A�adir a la estructura
			_forceRegistry->addRegistry(sfg1, pt1);
			_forceRegistry->addRegistry(sfg2, pt2);
			_forceGenerators.push_back(sfg1);
			_forceGenerators.push_back(sfg2);
			_particles.push_back(pt2);
		}
		else if (springType == PARTICLES_SPRING2) {
			// Part�cula
			pt1->setPos(				 Vector3(0, 120, 0));
			Particle* pt2 = new Particle(Vector3(0,  90, 0), Vector3(0), NONE, colors[BLUE],  CreateShape(PxSphereGeometry(3)), 60);
			Particle* pt3 = new Particle(Vector3(0,  60, 0), Vector3(0), NONE, colors[BLUE],  CreateShape(PxSphereGeometry(3)), 60);
			Particle* pt4 = new Particle(Vector3(0,  30, 0), Vector3(0), NONE, colors[RED] ,  CreateShape(PxSphereGeometry(3)), 60);

			// Generadores de muelles
			AnchoredSpringForceGenerator* spg = new AnchoredSpringForceGenerator(Vector3(0, 150, 0), 20, 10);
			SpringForceGenerator* sfg2_1 = new SpringForceGenerator(Vector3(0), 20, 10, pt1);
			SpringForceGenerator* sfg2_3 = new SpringForceGenerator(Vector3(0), 20, 10, pt3);
			SpringForceGenerator* sfg3_2 = new SpringForceGenerator(Vector3(0), 20, 10, pt2);
			SpringForceGenerator* sfg3_4 = new SpringForceGenerator(Vector3(0), 20, 10, pt4);
			SpringForceGenerator* sfg4_3 = new SpringForceGenerator(Vector3(0), 20, 10, pt3);

			// Conectar muelles
			_forceRegistry->addRegistry(spg, pt1);
			_forceRegistry->addRegistry(sfg2_1, pt2);
			_forceRegistry->addRegistry(sfg2_3, pt2);
			_forceRegistry->addRegistry(sfg3_2, pt3);
			_forceRegistry->addRegistry(sfg3_4, pt3);
			_forceRegistry->addRegistry(sfg4_3, pt4);

			// Fuerza de la gravedad
			_forceRegistry->addRegistry(gfc, pt1);
			_forceRegistry->addRegistry(gfc, pt2);
			_forceRegistry->addRegistry(gfc, pt3);
			_forceRegistry->addRegistry(gfc, pt4);

			// A�adir a la estructura
			_forceGenerators.push_back(spg);
			_forceGenerators.push_back(sfg2_1);
			_forceGenerators.push_back(sfg2_3);
			_forceGenerators.push_back(sfg3_2);
			_forceGenerators.push_back(sfg3_4);
			_forceGenerators.push_back(sfg4_3);

			// Part�culas
			_particles.push_back(pt2);
			_particles.push_back(pt3);
			_particles.push_back(pt4);
		}
		else if (springType == BUOYANCY_SPRING) {
			// � Fg > E ?
			BuoyancyForceGenerator* bfc1 = new BuoyancyForceGenerator(Vector3(0), 10, 30, 1000);

			// � Fg = E ? (to-do)
			Particle* pt2 = new Particle(Vector3(0, 50, -50), Vector3(0), NONE, colors[RED], CreateShape(PxSphereGeometry(3)), 60);
			BuoyancyForceGenerator* bfc2 = new BuoyancyForceGenerator(Vector3(0, 0, -50), 10, 30, 1000);

			// � Fg < E ? (to-do)
			Particle* pt3 = new Particle(Vector3(0, 50, -100), Vector3(0), NONE, colors[GREEN], CreateShape(PxSphereGeometry(3)), 60);
			BuoyancyForceGenerator* bfc3 = new BuoyancyForceGenerator(Vector3(0, 0, -100), 10, 30, 1000);

			// A�adir gravedad y flotaci�n
			_forceRegistry->addRegistry(bfc1, pt1);
			_forceRegistry->addRegistry(gfc, pt2);
			_forceRegistry->addRegistry(bfc2, pt2);
			_forceRegistry->addRegistry(gfc, pt3);
			_forceRegistry->addRegistry(bfc3, pt3);

			// A�adir a la estructura
			_forceGenerators.push_back(bfc1);
			_forceGenerators.push_back(bfc2);
			_forceGenerators.push_back(bfc3);

			// Part�culas
			_particles.push_back(pt2);
			_particles.push_back(pt3);
		}
		#pragma endregion
	}
}

// Destructora
ParticleSystem::~ParticleSystem() {
	// Borrar generadores
	for (ParticleGenerator* p : _particle_generators) delete p;
	_particle_generators.clear();

	// Borrar part�culas
	for (Particle* p : _particles) delete p;
	_particles.clear();

	// Borrar registro
	if (_forceRegistry != nullptr) delete _forceRegistry;

	// Borrar generadores
	for (ForceGenerator* fg : _forceGenerators) delete fg;
	_forceGenerators.clear();

	// Borrar part�culas no eliminadas
	for (int i = 0; i < _particlesToDelete.size(); i++) delete *_particlesToDelete[i];
	_particlesToDelete.clear();
}

// Update
void ParticleSystem::update(double t) {
	// Actualizar generadores (generar part�culas si procede)
	for (ParticleGenerator* p : _particle_generators) {
		list<Particle*> prtcls = p->generateParticles(t);
		if (!prtcls.empty()) {
			// A�adir fuerzas
			if (practiceType == FORCES_P3) {
				#pragma region Fuerzas (Pr�ctica 3 - Actividad 1)
				// Para generadores normales
				if (particlesType == GeneratorsType) {
					// Fuerza de la gravedad
					_forceRegistry->addRegistry(_forceGenerators[rand() % 2], *prtcls.begin());

					// Rozamiento (viento)
					if (forcesType == WIND) {
						_forceRegistry->addRegistry(_forceGenerators[WIND], *prtcls.begin());
						_forceRegistry->addRegistry(_forceGenerators[WIND2], *prtcls.begin());
						_forceRegistry->addRegistry(_forceGenerators[WIND3], *prtcls.begin());
						_forceRegistry->addRegistry(_forceGenerators[WIND4], *prtcls.begin());
					}
					// Tornado
					else if (forcesType == TORNADO) {
						_forceRegistry->addRegistry(_forceGenerators[TORNADO], *prtcls.begin());
					}				
				}

				// Para fireworks
				else if (particlesType == FireworksType)
					_forceRegistry->addRegistry(_forceGenerators[GRAVITY_DOWN], *prtcls.begin());
				#pragma endregion
			}
			
			// A�adir a la lista
			_particles.splice(_particles.end(), prtcls);
		}
	}

	// Actualizar fuerzas
	if (practiceType == FORCES_P3 || practiceType == SPRINGS_P4) {
		_forceRegistry->updateForces();
		_forceRegistry->updateTime(t);
	}

	// Actualizar part�culas y a�adir al vector de eliminaci�n si han muerto
	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);
	}

	// Eliminar las part�culas guardadas en el vector de eliminaci�n, borr�ndo tambi�n memoria
	for (int i = 0; i < _particlesToDelete.size(); i++) {
		Particle* p = *_particlesToDelete[i];

		// A�adir las nuevas part�culas generadas por la explosi�n de un firework
		if (particlesType == FireworksType) {
			#pragma region Fireworks
			// Obtener part�culas generadas al explotar
			list<Particle*> prtcls = static_cast<Firework*>(p)->explode();

			// A�adir fuerza de gravedad a todas las part�culas nuevas
			if (practiceType == FORCES_P3)
				for (Particle* p : prtcls) _forceRegistry->addRegistry(new GravityForceGenerator(Vector3(0, -10, 0)), p);
			
			// A�adir a la lista
			_particles.splice(_particles.end(), prtcls);
			#pragma endregion
		}
		
		// Borrar
		_forceRegistry->deleteParticleRegistry(p);
		_particles.erase(_particlesToDelete[i]);
		delete p;
	}
	_particlesToDelete.clear();
}

// Buscar y devolver un generador de part�culas con el nombre recibido
ParticleGenerator* ParticleSystem::getParticleGenerator(string name) {
	auto it = _particle_generators.begin();
	bool enc = false;
	while (!enc && it != _particle_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return (*it);
}

// Buscar y devolver un generador de fuerzas con el nombre recibido
ForceGenerator* ParticleSystem::getForceGenerator(string name) {
	auto it = _forceGenerators.begin();
	bool enc = false;
	while (!enc && it != _forceGenerators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return (*it);
}

// Crea todas las fuerzas y las a�ade a al vector de estas
void ParticleSystem::createForces() {
	// Gravedad
	_forceGenerators.push_back(new GravityForceGenerator(Vector3(0, -10, 0)));
	_forceGenerators.push_back(new GravityForceGenerator(Vector3(0, 10, 0)));
	// Viento
	_forceGenerators.push_back(new WindForceGenerator(Vector3(0), Vector3(0, 0, -200), 50, colors[BLUE], 10));
	_forceGenerators.push_back(new WindForceGenerator(Vector3(50, 20, -100), Vector3(-200, 0, 0), 50, colors[RED], 10));
	_forceGenerators.push_back(new WindForceGenerator(Vector3(-100, 30, -170), Vector3(0, 0, 200), 50, colors[GREEN], 10));
	_forceGenerators.push_back(new WindForceGenerator(Vector3(-150, 45, -40), Vector3(0, 600, 0), 50, Vector4(0, 0, 255, 1), 10));
	// Tornado
	_forceGenerators.push_back(new TornadoForceGenerator(Vector3(0), 600, 10));
	// Explosi�n
	_forceGenerators.push_back(new ExplosionForceGenerator(Vector3(0), 80, 400000, 0.1));
}

// Crea los generadores y las part�culas especificas para el viento y el tornado
void ParticleSystem::createWindOrTornadoParticles() {
	ParticleGenerator* ptGen = nullptr;
	Particle* model = nullptr;
	if (forcesType == WIND) {
		model = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
		ptGen = new GaussianParticleGenerator("Gaussian", model, model->getPos(), Vector3(5), 0);
	}
	else if (forcesType == TORNADO) {
		model = new Particle(Vector3(0), Vector3(0), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
		ptGen = new GaussianParticleGenerator("Gaussian", model, model->getPos(), Vector3(0.001, 0.001, 0.001), 0, false,
			Vector3(10, 0.0001, 10));
		//model->setBoundaries(Vector3(600, 600, 600));
	}
	if (ptGen != nullptr) _particle_generators.push_back(ptGen);
}

// Crea part�culas en torno a una esfera
void ParticleSystem::createParticleSpheres(int n, int rad) {
	int a = 360 / n; float pi = 3.141516;
	for (int i = 0; i < n; i++) {
		float theta = rand() % 360;
		float phi = rand() % 360;

		float x = rad * sin(theta * pi / 180.0f) * cos(phi * pi / 180.0f);
		float y = rad * sin(theta * pi / 180.0f) * sin(phi * pi / 180.0f);
		float z = rad * cos(theta * pi / 180.0f);

		Particle* p;
		if (i < n * 1 / 5) p = new Particle(Vector3(x, y, z), Vector3(0), NONE, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		else if (i < n * 2 / 5) p = new Particle(Vector3(x + rad * 4, y, z), Vector3(0), NONE, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		else if (i < n * 3 / 5) p = new Particle(Vector3(x, y + rad * 4, z), Vector3(0), NONE, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		else if (i < n * 4 / 5) p = new Particle(Vector3(x, y - rad * 4, z), Vector3(0), NONE, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		else if (i < n) p = new Particle(Vector3(x - rad * 4, y, z), Vector3(0), NONE, colors[rand() % 4], CreateShape(PxSphereGeometry(2)), rand() % 1000);
		
		_particles.push_back(p);
	}
}

// Control del input de las explosiones
bool ParticleSystem::createExplosion(bool expl) {
	if (forcesType == EXPLOSION) {
		for (Particle* p : _particles) {
			if (expl) {
				_forceRegistry->addRegistry(_forceGenerators[EXPLOSION], p);
				//_forceRegistry->addRegistry(_forceGenerators[GRAVITY_DOWN], p);
				return false;
			}
			else {
				p->reset();
				_forceRegistry->deleteParticleRegistry(p);
				_forceRegistry->updateTime(0);
			}
		}
	}

	return true;
}

// Activa el generador de viento (pr�ctica 4)
void ParticleSystem::setWindActive() {
	bool active = _forceGenerators[WIND_GEN]->getActive();
	_forceGenerators[WIND_GEN]->setActive(!active);
	!active ? cout << "Viento activado" : cout << "Viento desactivado";
	cout << "\n";
}

// Cambia la k del muelle
void ParticleSystem::changeKSpring(char t) {
	SpringForceGenerator* spg1;
	if (springType == STATIC_SPRING) {
		spg1 = static_cast<SpringForceGenerator*>(_forceGenerators[springType]);
		t == '+' ? spg1->setK(spg1->getK() + 1) : spg1->setK(spg1->getK() - 1);
	}
	else if (springType == PARTICLES_SPRING) {
		spg1 = static_cast<SpringForceGenerator*>(_forceGenerators[springType - 1]);
		SpringForceGenerator* spg2 = static_cast<SpringForceGenerator*>(_forceGenerators[springType]);
		int sign = t == '+' ? 1 : -1;
		spg1->setK(spg1->getK() + (1 * sign));
		spg2->setK(spg2->getK() + (1 * sign));
	}
	
	cout << "k: " << spg1->getK();
	t == '+' ? cout << " (+)\n" : cout << " (-)\n";
}