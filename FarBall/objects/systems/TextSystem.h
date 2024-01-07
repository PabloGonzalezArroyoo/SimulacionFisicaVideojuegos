#pragma once
#include "../../structure/states/GameState.h"
#include "../../structure/ecs/System.h"

class TextSystem : public System {
private:
	STATE state;
	float elapsedTime;

public:
	constexpr static sysId_type id = _sys_TEXT;

	// Métodos virtuales
	void update(double t);

	void flickerText(double t);
	void removeTexts();

	// Setters
	inline void setState(STATE st) { state = st; }
	
};