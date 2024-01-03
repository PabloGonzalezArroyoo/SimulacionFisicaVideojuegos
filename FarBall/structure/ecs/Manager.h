#pragma once
#include "Constants.h"
#include "../../objects/physicObjects/Actor.h"
#include "System.h"
#include <vector>
#include <array>

using namespace std;

class Manager {
private:
	// Estructura de entidades -> array de vectores
	array<vector<Actor*>, maxGroupId> entsByGroup;
	array<Actor*, maxHandlerId> handlers;
	array<System*, maxSystemId> sys;

public:
	// Constructora y destructora
	Manager() {
		for (auto& groupEntities : entsByGroup) {
			groupEntities.reserve(100);
		}
	}
	virtual ~Manager() {
		for (int i = 0; i < maxGroupId; i++) {
			for (auto g : entsByGroup[i]) delete g;
		}
	}

	// Métodos esenciales
	void refresh() {
		for (grpId_type gId = 0; gId < maxGroupId; gId++) {
			auto& grpEnts = entsByGroup[gId];
			grpEnts.erase(
				remove_if(grpEnts.begin(), grpEnts.end(),
					[](Actor* g) {
						if (g->getAlive()) return false;
						else { delete g; return true; }
					}), grpEnts.end()
						);
		}
	}
	void update(double t) {
		for (System* s : sys) {
			if (s != nullptr) s->update();
		}
	}

	// Para añadir una entidad al manager
	Actor* addActor(Actor* a, grpId_type gId = _grp_GENERAL) {
		entsByGroup[gId].push_back(a);
		return a;
	}

	// Getters
	const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup[gId];
	}

	// Elimina todas las entidades de un grupo deseado
	void removeEntities(grpId_type gId) {
		for (Actor* a : entsByGroup[gId]) {
			a->setAlive(false);
		}
	}

	inline Actor* getHandler(hdlrId_type hId) {
		return handlers[hId];
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
};