#include "Firework.h"

Firework::Firework(Particle* m, FireworkGenerator* g, int gn, pair<int, int> cLimits) :
	Particle(m->getPos(), m->getVelocity(), m->getLifeTime(), m->getColor(), m->getShape()), generations(gn),
	generator(g), childLimits(cLimits) {
}

list<Particle*> Firework::explode() {
	list<Particle*> lista;

	if (generations > 0) {
		int randomChilds = rand() % childLimits.second + childLimits.first;
		for (int i = 0; i < randomChilds; i++) {
			Firework* fr = clone(this, childLimits);
			generator->recalculateDistributions(fr->getVelocity());
			fr->setVelocity(generator->obtainDistributionVelValues());
			lista.push_back(fr);
		}
	}
	else generator->resetGenerator();

	return lista;
}

Firework* Firework::clone(Particle* m, pair<int, int> c) const {
	return new Firework(m, generator, generations - 1, c);
}