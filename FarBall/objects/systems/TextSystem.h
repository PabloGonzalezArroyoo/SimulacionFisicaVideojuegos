#pragma once
#include "../../structure/ecs/System.h"

class TextSystem : public System {
private:
	float elapsedTime;

public:
	constexpr static sysId_type id = _sys_TEXT;

	// Métodos virtuales
	virtual void update(double t);
	virtual void receive(const Message& m);

	void flickerText(double t);
	void updateDistance(int x);
	void removeTexts();

	// Setters
	void setPlayState();
};