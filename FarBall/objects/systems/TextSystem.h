#pragma once
#include "../../structure/ecs/System.h"
#include "../../objects/physicObjects/RigidBody.h"

class TextSystem : public System {
private:
	float elapsedTime;
	RigidBody* pointsUI;
	RigidBody* titleUI;

public:
	constexpr static sysId_type id = _sys_TEXT;

	// Métodos virtuales
	virtual void update(double t);
	virtual void receive(const Message& m);

	void flickerText(double t);
	void updateDistance(int x);
	void updateFuel(int fuel);
	void addFuel();
	void removeTexts();

	// Setters
	void setPlayState();
};