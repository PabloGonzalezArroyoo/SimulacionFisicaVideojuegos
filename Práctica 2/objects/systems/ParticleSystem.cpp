#include "ParticleSystem.h"

// Constructora
ParticleSystem::ParticleSystem() {

	#pragma region Particulas (Actividad 1)
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

	//// Generador no estático
	//Particle* model = new Particle(Vector3(0), Vector3(50), TIME, colors[BLUE], CreateShape(PxBoxGeometry(2, 2, 2)));
	////model->setBoundaries(Vector3(200));
	//ParticleGenerator*  ptGen = new UniformParticleGenerator("Uniform", model, model->getPos() + Vector3(-100, 0, 0), Vector3(35), 0, false, Vector3(20));
	//_particle_generators.push_back(ptGen);
	#pragma endregion

	#pragma region Fireworks (Actividad 2)
	//// Generador de fireworks amarillos
	//Particle* pt = new Particle(Vector3(0), Vector3(50), TIME, colors[YELLOW], CreateShape(PxSphereGeometry(3)));
	//pt->setLifeTime(2);
	//Firework* model = new Firework(pt, nullptr, 3, make_pair(3, 5)); // true para cambiar colores, false predeterminado
	//pt->setInvisible(); 
	//ParticleGenerator* ptGen = new FireworkGenerator("FireworksY1", model, Vector3(0), Vector3(15, 10, 15));
	//_particle_generators.push_back(ptGen);

	//// Generador de fireworks azules
	//pt = new Particle(Vector3(0), Vector3(80), TIME, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)));
	//pt->setLifeTime(2);
	//model = new Firework(pt, nullptr, 4, make_pair(5, 8));
	//pt->setInvisible();
	//ptGen = new FireworkGenerator("FireworksB1", model, Vector3(-100, 0, -100), Vector3(30, 25, 30));
	//_particle_generators.push_back(ptGen);

	//// Generador de fireworks verdes
	//pt = new Particle(Vector3(0), Vector3(100), TIME, colors[GREEN], CreateShape(PxBoxGeometry(2, 2, 2)));
	//pt->setLifeTime(2);
	//model = new Firework(pt, nullptr, 5, make_pair(8, 10));
	//pt->setInvisible(); 
	//ptGen = new FireworkGenerator("Fireworks", model, Vector3(-200, 0, -200), Vector3(40, 30, 40));
	//_particle_generators.push_back(ptGen);
	#pragma endregion

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
		if (!prtcls.empty()) _particles.splice(_particles.end(), prtcls);
	}

	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);
	}

	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _particlesToDelete.size(); i++) {
		Particle* p = *_particlesToDelete[i];

		#pragma region Fireworks (Actividad 2)
		// Añadir las nuevas partículas generadas por la explosión de un firework
		//_particles.splice(_particles.end(), static_cast<Firework*>(p)->explode());
		#pragma endregion
		
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