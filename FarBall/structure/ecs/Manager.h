#pragma once
#include "../../objects/physicObjects/Actor.h"
#include "../../objects/systems/ForceRegistry.h"
#include "System.h"
#include <vector>
#include <array>
#include <list>
#include <assert.h>

using namespace std;

class Manager {
private:
	// Estructura
	array<list<Actor*>, maxGroupId> objects;
	array<Actor*, maxHandlerId> handlers;
	array<System*, maxSystemId> sys;
	vector<Message> msgs;
	vector<Message> aux_msgs;

	// Físicas
	PxScene* gScene;
	PxPhysics* gPhysics;
	ForceRegistry* forceRegistry;

public:
	// Constructora y destructora
	Manager(PxScene* gs, PxPhysics* ph) : objects(), handlers(), sys(), gScene(gs), gPhysics(ph), 
		forceRegistry(new ForceRegistry()) {};
	virtual ~Manager() {
		for (int i = 0; i < maxGroupId; i++) {
			for (auto g : objects[i]) delete g;
		}

		for (int i = 0; i < maxSystemId; i++) {
			delete sys[i];
			sys[i] = nullptr;
		}
	}

	// Métodos esenciales
	void refresh() {
		for (grpId_type gId = 0; gId < maxGroupId; gId++) {
			auto& grpEnts = objects[gId];
			grpEnts.erase(
				remove_if(grpEnts.begin(), grpEnts.end(),
					[](Actor* a) {
						if (a->getAlive()) return false;
						else { delete a; return true; }
					}), grpEnts.end()
						);
		}
	}
	void update(double t) {
		for (System* s : sys) {
			if (s != nullptr) s->update(t);
			forceRegistry->updateForces();
			forceRegistry->updateTime(t);
		}
	}

	// ----- METODOS QUE AÑADEN -----
	// Para añadir una entidad al manager
	Actor* addActor(grpId_type gId, Actor* a) {
		objects[gId].push_back(a);
		return a;
	}

	// Para añadir un sistema
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys[sId] = s;
		return static_cast<T*>(s);
	}

	// ----- METODOS QUE QUITAN -----
	// Elimina todas las entidades de un grupo deseado
	void removeEntities(grpId_type gId) {
		for (Actor* a : objects[gId]) {
			a->setAlive(false);
		}
	}

	// Elimina un sistema
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys[sId] != nullptr) {
			delete sys[sId];
			sys[sId] = nullptr;
		}
	}

	//	----- GETTERS -----
	// Devuelve un objeto especifico
	inline Actor* getHandler(hdlrId_type hId) {
		assert(handlers[hId] != nullptr);
		return handlers[hId];
	}

	// Devuelve un grupo de actores
	inline const auto& getActors(grpId_type gId = _grp_GENERAL) {
		return objects[gId];
	}

	// Devuelve el sistema especifico
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys[sId]);
	}
	
	inline PxScene* getScene() {
		return gScene;
	}

	inline PxPhysics* getPhysics() {
		return gPhysics;
	}

	inline ForceRegistry* getForceRegistry() {
		return forceRegistry;
	}

	// ----- SETTERS -----
	inline void setHandler(hdlrId_type hId, Actor* a) {
		handlers[hId] = a;
	}

	inline void setAlive(Actor* a, bool alive) {
		a->setAlive(alive);
	}

	// ----- CHECKERS -----
	// Comprueba si la entidad está viva
	inline bool isAlive(Actor* a) {
		return a->getAlive();
	}

	// ----- MESSAGES -----
	inline void send(const Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : sys) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		else {
			msgs.emplace_back(m);
		}
	}

	inline void flushMessages() {
		std::swap(msgs, aux_msgs);
		for (auto& m : aux_msgs) {
			for (System* s : sys) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		aux_msgs.clear();
	}
};