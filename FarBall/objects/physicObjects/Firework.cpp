#include "Firework.h"

Firework::Firework(Actor* m, FireworkGenerator* g, int gn, pair<int, int> cLimits, bool cc) :
	Particle(m->getPos(), m->getVelocity(), m->getState(), m->getColor(), m->getShape()), generations(gn), generator(g),
	childLimits(cLimits), changeColor(cc) {
	lifeTime = m->getLifeTime();
}

list<Actor*> Firework::explode() {
	list<Actor*> lista;

	int randomChilds, randomColor;
	if (generations > 0) {
		randomChilds = rand() % childLimits.second + childLimits.first;
		if (changeColor) { int randomColor = rand() % colors.size(); setColor(colors[randomColor]); }
		for (int i = 0; i < randomChilds; i++) {
			Firework* fr = clone(this, childLimits, changeColor);
			generator->recalculateDistributions(fr->getVelocity());
			fr->setVelocity(generator->obtainDistributionVelValues());
			lista.push_back(fr);
		}
	}
	else generator->resetGenerator();

	return lista;
}

Firework* Firework::clone(Actor* m, pair<int, int> c, bool cc) const {
	return new Firework(m, generator, generations - 1, c, cc);
}