#pragma once

#include "Actor.h"

class RigidBody : public Actor {
private:
	// Físicas
	PxPhysics* gPhysics;
	PxScene* gScene;

	// Sólidos
	bool dynamic;
	PxRigidDynamic* dnRigid = nullptr;
	PxRigidStatic* stRigid = nullptr;

public:
	// Constructora y destructora
	RigidBody(PxPhysics* p, PxScene* sc, PxTransform t, PxShape* s, ElimState st, Vector4 c, float m, bool d = true);
	virtual ~RigidBody();

	// Actualizar
	bool integrate(double t);
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
	inline Vector3 getSize() {
		Vector3 size;
		if (shape->getGeometryType() == PxGeometryType::eBOX) {
			PxBoxGeometry box;
			shape->getBoxGeometry(box);
			size = box.halfExtents;
		}
		return size;
	}
	inline int getVolume() { 
		Vector3 size = getSize();
		return size.x * size.y * size.z;
	}
	inline PxRigidDynamic* getDynRigid() { return dnRigid; }
	inline PxRigidStatic* getStRigid() { return stRigid; }
};

