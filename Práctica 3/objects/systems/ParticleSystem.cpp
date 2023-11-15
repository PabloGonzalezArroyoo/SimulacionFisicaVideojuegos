#include "ParticleSystem.h"

// Constructora
ParticleSystem::ParticleSystem() {
	if (practiceType == PARTICLES_P2A1) {
		#pragma region Particulas (Práctica 2 - Actividad 1)
		// Generador de partículas amarillas redondas
		Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
		//model->setBoundaries(Vector3(100));
		ParticleGenerator* ptGen = new GaussianParticleGenerator("Gaussian", model, model->getPos(), Vector3(35), 0);
		_particle_generators.push_back(ptGen);

		// Generador de partículas azules cuadradas
		model = new Particle(Vector3(0), Vector3(50), TIME, colors[BLUE], CreateShape(PxBoxGeometry(2, 2, 2)));
		//model->setBoundaries(Vector3(200));
		ptGen = new UniformParticleGenerator("Uniform", model, model->getPos() + Vector3(-100, 0, 0), Vector3(35), 0);
		_particle_generators.push_back(ptGen);

		// Generador no estático
		//Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[BLUE], CreateShape(PxBoxGeometry(2, 2, 2)));
		////model->setBoundaries(Vector3(200));
		//ParticleGenerator*  ptGen = new UniformParticleGenerator("Uniform", model, model->getPos() + Vector3(-100, 0, 0), Vector3(35), 0, false, Vector3(20));
		//_particle_generators.push_back(ptGen);	
		#pragma endregion
	}	

	else if (practiceType == FIREWORKS_P2A2) {
		#pragma region Fireworks (Práctica 2 - Actividad 2)
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

	else if (practiceType == FORCES_P3A1) {
		#pragma region Fuerzas (Práctica 3 - Actividad 1)
		if (particlesType == GeneratorsType) {
			// Generador de partículas amarillas redondas
			Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)), 10);
			ParticleGenerator* ptGen = new GaussianParticleGenerator("Gaussian", model, model->getPos(), Vector3(5), 0.5);
			_particle_generators.push_back(ptGen);
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

		// Contenedor de fuerzas
		_forceRegistry = new ParticleForceRegistry();
		#pragma endregion
	}
}

// Destructora
ParticleSystem::~ParticleSystem() {
	// Borrar generadores
	for (ParticleGenerator* p : _particle_generators) delete p;
	_particle_generators.clear();

	// Borrar partículas
	for (Particle* p : _particles) delete p;
	_particles.clear();

	// Borrar partículas no eliminadas
	for (int i = 0; i < _particlesToDelete.size(); i++) delete *_particlesToDelete[i];
	_particlesToDelete.clear();
}

// Update
void ParticleSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (ParticleGenerator* p : _particle_generators) {
		list<Particle*> prtcls = p->generateParticles(t);
		if (!prtcls.empty()) {
			// Añadir fuerzas
			if (practiceType == FORCES_P3A1) {
				#pragma region Fuerzas (Práctica 3 - Actividad 1)
				// Para generadores normales
				if (particlesType == GeneratorsType) {
					// Fuerza de la gravedad
					rand() % 2 == 0 ?
						_forceRegistry->addRegistry(new GravityForceGenerator(Vector3(0, -10, 0)), *prtcls.begin()) :
						_forceRegistry->addRegistry(new GravityForceGenerator(Vector3(0, 10, 0)), *prtcls.begin());

					// Rozamiento (viento)
					_forceRegistry->addRegistry(new WindForceGenerator(20, 0), *prtcls.begin());
				}

				// Para fireworks
				else if (particlesType == FireworksType)
					_forceRegistry->addRegistry(new GravityForceGenerator(Vector3(0, -10, 0)), *prtcls.begin());
				#pragma endregion
			}
			
			// Añadir a la lista
			_particles.splice(_particles.end(), prtcls);
		}
	}

	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);
	}

	// Actualizar fuerzas
	if (practiceType == FORCES_P3A1) _forceRegistry->updateForces();

	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _particlesToDelete.size(); i++) {
		Particle* p = *_particlesToDelete[i];

		// Añadir las nuevas partículas generadas por la explosión de un firework
		if (particlesType == FireworksType) {
			#pragma region Fireworks
			// Obtener partículas generadas al explotar
			list<Particle*> prtcls = static_cast<Firework*>(p)->explode();

			// Añadir fuerza de gravedad a todas las partículas nuevas
			if (practiceType == FORCES_P3A1)
				for (Particle* p : prtcls) _forceRegistry->addRegistry(new GravityForceGenerator(Vector3(0, -10, 0)), p);
			
			// Añadir a la lista
			_particles.splice(_particles.end(), prtcls);
			#pragma endregion
		}
		
		// Borrar
		_particles.erase(_particlesToDelete[i]);
		delete p;
	}
	_particlesToDelete.clear();
}

// Buscar y devolver un generador con el nombre recibido
ParticleGenerator* ParticleSystem::getParticleGenerator(string name) {
	auto it = _particle_generators.begin();
	bool enc = false;
	while (!enc && it != _particle_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return (*it);
}