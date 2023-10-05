#pragma once

#include "Particle.h"

enum shotType {
	// REVOLER:
	// masa real = 230 g
	// vel real = 253 m/s
	// vel sim = 25 m/s
	// Por tanto, masa simulada = 23.56 kg
	REVOLER,

	// FIREBALL:
	// masa real = 1*10^-7 g
	// vel real = 6 m/s
	// vel sim = 20 m/s
	// Por tanto, masa simulada = 0.1 kg (aproximación)
	FIREBALL,

	// LASER:
	// masa real = 0 g
	// vel real = 3*10^8 m/s
	// vel sim = 100 m/s
	// Por tanto, masa simulada = 0.1kg (aproximación)
	LASER,

	// TANK:
	// masa real = 20000 g
	// vel real = 180 m/s
	// vel sim = 50 m/s
	// Por tanto, masa simulada = 259.2 kg
	TANK
};

class Projectile : public Particle {
private:

public:
	Projectile(PxTransform tr, Vector3 dir, float lTime, int tipo);

	virtual bool integrate(double t);
};

