#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	Particle* model = new Particle(10, Vector3(0), Vector3(50), Vector3(0), 0, Vector4(125, 125, 0, 1), CreateShape(PxSphereGeometry(3)));
	ParticleGenerator* ptGen = new GaussianParticleGenerator(Vector3(0), Vector3(35), 0.3, model);
	_particle_generators.push_back(ptGen);

	model = new Particle(10, Vector3(0), Vector3(50), Vector3(0), 0, Vector4(0, 125, 125, 1), CreateShape(PxBoxGeometry(2, 2, 2)));
	ptGen = new GaussianParticleGenerator(Vector3(-150, 0, 0), Vector3(35), 0.3, model);
	_particle_generators.push_back(ptGen);
}

ParticleSystem::~ParticleSystem() {
	// Actualizar generadores (generar partículas si procede)
	for (ParticleGenerator* p : _particle_generators) delete p;
	_particle_generators.clear();

	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (Particle* p : _particles) delete p;
	_particles.clear();
}

void ParticleSystem::update(double t) {
	// Actualizar generadores (generar partículas si procede)
	for (ParticleGenerator* p : _particle_generators) {
		list<Particle*> prtcls = p->generateParticles();
		if (!prtcls.empty()) _particles.splice(_particles.end(), prtcls);
	}

	// Actualizar partículas y añadir al vector de eliminación si han muerto
	for (auto it = _particles.begin(); it != _particles.end(); it++) {
		if (!(*it)->integrate(t)) _particlesToDelete.push_back(it);
	}

	// Eliminar las partículas guardadas en el vector de eliminación, borrándo también memoria
	for (int i = 0; i < _particlesToDelete.size(); i++) {
		Particle* p = *_particlesToDelete[i];
		_particles.erase(_particlesToDelete[i]);
		delete p;
	}
	_particlesToDelete.clear();
}

ParticleGenerator* ParticleSystem::getParticleGenerator(string name) {
	auto it = _particle_generators.begin();
	bool enc = false;
	while (!enc && it != _particle_generators.end()) {
		enc = (*it)->getName() == name;
		if (!enc) it++;
	}

	return (*it);
}

void ParticleSystem::generateFireworkSystem() {

}