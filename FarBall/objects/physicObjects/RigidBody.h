#pragma once

#include "Actor.h"

class RigidBody : public Actor {
private:
	// F�sicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	// S�lidos
	bool dynamic;
	PxRigidDynamic* dnRigid = nullptr;
	PxRigidStatic* stRigid = nullptr;

public:
	// Constructora y destructora
	RigidBody(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m, bool d = true);
	virtual ~RigidBody();

	// Actualizar
	virtual void integrate(double t);
	virtual void addForce(const Vector3& f) { if (dnRigid != nullptr) dnRigid->addForce(f); }
	virtual void clearForce() { if (dnRigid != nullptr) dnRigid->clearForce(); }

	void disableGravity() { if (dnRigid != nullptr) dnRigid->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true); }

	// Clonar
	RigidBody* clone() const;
	RigidBody* clone(PxTransform t, Vector3 v = Vector3(0)) const;

	// Getters y setters
	virtual inline float getMass() { return dnRigid != nullptr ? dnRigid->getMass() : 1e-10; };
	inline Vector3 getVelocity() { return dnRigid != nullptr ? dnRigid->getLinearVelocity() : Vector3(0); }
	inline void setVelocity(Vector3 v) { if (dnRigid != nullptr) dnRigid->setLinearVelocity(Vector3(v)); }
	virtual inline void setMass(float m) { 
		if (dnRigid != nullptr) {
			dnRigid->setMass(m);
			PxRigidBodyExt::setMassAndUpdateInertia(*static_cast<PxRigidBody*>(dnRigid), getMass() / getVolume());
		}
	}
	virtual inline void setPos(Vector3 t) {
		if (dnRigid != nullptr) {
			Actor::setPos(t);
			dnRigid->setGlobalPose(PxTransform(t));
		}
	}
	inline int getVolume() { 
		int vol = 0;
		if (shape->getGeometryType() == PxGeometryType::eBOX) {
			PxBoxGeometry box;
			shape->getBoxGeometry(box);
			Vector3 dims = box.halfExtents;
			vol = dims.x * dims.y * dims.z;
		}
		else if (shape->getGeometryType() == PxGeometryType::eSPHERE) {
			PxSphereGeometry sph;
			shape->getSphereGeometry(sph);
			vol = sph.radius;
		}
		return vol;
	}
	inline PxRigidDynamic* getDynRigid() { return dnRigid; }
	inline PxRigidStatic* getStRigid() { return stRigid; }
};

