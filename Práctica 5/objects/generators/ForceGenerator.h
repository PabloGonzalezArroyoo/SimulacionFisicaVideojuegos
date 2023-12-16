#pragma once

#include "../physicObjects/Particle.h"
#include "../physicObjects/RigidBody.h"
#include <numbers>

using namespace std;

#pragma region FORCE GENERATOR
class ForceGenerator {
protected:
	string name;
	double t = 0.0, lifeTime = -1e10;
	Vector3 pos;
	bool active;

public:
	ForceGenerator(Vector3 p) : pos(p), active(true) {};
	virtual ~ForceGenerator() {}

	virtual void updateForce(Actor* actor) = 0;

	inline void updateTime(double _t) { t += _t; }

	/*inline bool updateTime(double _t) {
		t += _t;
		return t < lifeTime || lifeTime < 0.0;
	}*/

	inline void resetTime() { t = 0; }

	inline void setActive(bool a) { active = a; }
	inline bool getActive() { return active; }
	inline string getName() { return name; }
};
#pragma endregion

#pragma region GRAVITY FORCE
class GravityForceGenerator : public ForceGenerator {
protected:
	Vector3 gravity;

public:
	GravityForceGenerator(const Vector3& g) : ForceGenerator(Vector3(0)), gravity(g) {
		name = "gravity";
	}

	virtual void updateForce(Actor* actor) {
		if (active && fabs(actor->getMass()) > 1e-10)
			actor->addForce(gravity * actor->getMass());
	}

	inline void setGravity(Vector3 g) { gravity = g; }
};
#pragma endregion

#pragma region WIND FORCE
class WindForceGenerator : public ForceGenerator {
protected:
	// k1 -> velocidad, k2 -> velocidad cuadrática
	float k1, k2;
	Vector3 vel;
	float size;

	RenderItem* renderItem = nullptr;

public:
	~WindForceGenerator() { if (renderItem != nullptr) renderItem->release(); };
	WindForceGenerator(Vector3 p, Vector3 v, float s, Vector4 c, const float _k1, bool txt = false, const float _k2 = 0) : ForceGenerator(pos),
		vel(v), size(s), k1(_k1), k2(_k2) {
		name = "wind";
		pos = p;
		if (txt) renderItem = new RenderItem(CreateShape(PxBoxGeometry(s, 1, s)), new PxTransform(p), c);
	}

	virtual void updateForce(Actor* actor) {
		if (active && fabs(actor->getMass()) > 1e-10 && insideLimit(actor->getPos())) {
			Vector3 diffVel = vel - actor->getVelocity();
			Vector3 dragF = k1 * diffVel + k2 * diffVel.magnitude() * diffVel;
			actor->addForce(dragF);
		}
	}
	virtual bool insideLimit(Vector3 p) {
		return p.x < pos.x + size
			&& p.x > pos.x - size
			&& p.z < pos.z + size
			&& p.z > pos.z - size;
	}

	inline void setInvisible() { renderItem->release(); }
	inline void setDrag(float _k1, float _k2) { k1 = _k1; k2 = _k2; }
	inline float getK1() { return k1; }
	inline float getK2() { return k2; }
};
#pragma endregion

#pragma region TORNADO FORCE
class TornadoForceGenerator : public WindForceGenerator {
private:
	float k;

public:
	TornadoForceGenerator(Vector3 p, float size, float _k) : WindForceGenerator(p, Vector3(0), size, Vector4(0, 0, 0, 1), 1),
		k(_k) { }

	virtual void updateForce(Actor* actor) {
		if (active && fabs(actor->getMass()) > 1e-10 && insideLimit(actor->getPos())) {
			Vector3 diff = actor->getPos() - pos;
			Vector3 vel = k * Vector3(-diff.z, 50 - diff.y, diff.x);
			actor->addForce(vel);

			//WindForceGenerator::updateForce(actor);
		}
	}

	virtual bool insideLimit(Vector3 p) {
		return p.x < pos.x + size
			&& p.x > pos.x - size
			&& p.z < pos.z + size
			&& p.z > pos.z - size;
	}
};
#pragma endregion

#pragma region EXPLOSION FORCE
class ExplosionForceGenerator : public ForceGenerator {
private:
	float radius, k, tau;

public:
	ExplosionForceGenerator(Vector3 p, float r, float _k, float _tau) : ForceGenerator(Vector3(0)), radius(r),
		k(_k), tau(1 / _tau) {
		name = "explosion";
	}

	virtual void updateForce(Actor* actor) {
		if (active && fabs(actor->getMass()) > 1e-10) {
			Vector3 pPos = actor->getPos();
			float r = (pPos - pos).magnitude();

			if (insideLimit(r)) {
				Vector3 force = k / powf(r, 2) * Vector3(pPos.x - pos.x, pPos.y - pos.y, pPos.z - pos.z) * exp(-t / tau);
				actor->addForce(force);
			}
		}
	}

	bool insideLimit(float r) {
		return r < radius;
	}
};
#pragma endregion

#pragma region SPRING FORCE
class SpringForceGenerator : public ForceGenerator {
protected:
	double k, resisting_length;
	Actor* other;
	bool elastic;

public:
	SpringForceGenerator(Vector3 pos, double _k, double rl, Actor* oth, bool el = false) : ForceGenerator(pos), k(_k),
		resisting_length(rl), other(oth), elastic(el) {
		//other = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(1, 1, 1)));
	}

	virtual void updateForce(Actor* actor) {
		// actor -> particula a la que se le añade la fuerza
		if (active) {
			Vector3 relativePosVector = other->getPos() - actor->getPos();
			if (elastic && relativePosVector.magnitude() < resisting_length)
				return;

			double length = relativePosVector.normalize();
			float deltaX = length - resisting_length;

			Vector3 force = relativePosVector * deltaX * k;
			actor->addForce(force);
		}
	}

	inline void setK(double _k) { k = _k; }
	inline double getK() { return k; }
};
#pragma endregion

#pragma region ANCHORED FORCE
class AnchoredSpringForceGenerator : public SpringForceGenerator {
public:
	AnchoredSpringForceGenerator(Vector3 pos, double _k, double rl) : SpringForceGenerator(pos, _k, rl, nullptr) {
		name = "anchoredSpring";
		other = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(3, 3, 3)), 1e6);
	}

	virtual void updateForce(Actor* actor) {
		// actor -> particula a la que se le añade la fuerza
		if (active) {
			Vector3 relativePosVector = pos - actor->getPos();
			if (elastic && relativePosVector.magnitude() < resisting_length)
				return;

			double length = relativePosVector.normalize();
			float deltaX = length - resisting_length;

			Vector3 force = relativePosVector * deltaX * k;
			actor->addForce(force);
		}
	}

	~AnchoredSpringForceGenerator() { delete other; }
};
#pragma endregion

#pragma region BUOYANCY FORCE
class BuoyancyForceGenerator : public ForceGenerator {
private:
	float height, volume, liquidDensity, gravity = 9.8;

	Actor* liquidParticle;

public:
	BuoyancyForceGenerator(Vector3 pos, float h, float v, float d) : ForceGenerator(pos), height(h), volume(v),
		liquidDensity(d) {
		name = "buoyancy";
		liquidParticle = new Particle(pos, Vector3(0), NONE, colors[BLUE], CreateShape(PxBoxGeometry(h * 10, h / 10, h * 10)));
	}
	virtual ~BuoyancyForceGenerator() { delete liquidParticle; }

	virtual void updateForce(Actor* actor) {
		float h = actor->getPos().y;
		float h0 = liquidParticle->getPos().y;

		float inmersed = 0.0;
		if (h - h0 > height * 0.5) inmersed = 0.0;
		else if (h0 - h > height * 0.5) inmersed = 1.0;
		else inmersed = (h0 - h) / height + 0.5;

		Vector3 force = Vector3(0, liquidDensity * volume * inmersed * gravity, 0);
		actor->addForce(force);
	}

	void setVolume(float v) { volume = v; }
	float getVolume() { return volume; }
	void setHeight(float h) { height = h; }
	float getHeight() { return height; }
};
#pragma endregion
