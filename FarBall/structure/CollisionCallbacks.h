#include <PxPhysicsAPI.h>
#include "../objects/physicObjects/RigidBody.h"

class CollisionCallbacks : public physx::PxSimulationEventCallback {
public:
    virtual void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override {
        
        for (physx::PxU32 i = 0; i < nbPairs; i++) {
            const physx::PxContactPair& cp = pairs[i];

            if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND) {

            }
        }
    }

    virtual void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override {
    }

    virtual void onWake(physx::PxActor** actors, physx::PxU32 count) override {
    }

    virtual void onSleep(physx::PxActor** actors, physx::PxU32 count) override {
    }

    virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override {
    }

    virtual void onAdvance(const physx::PxRigidBody* const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override {
    }


};