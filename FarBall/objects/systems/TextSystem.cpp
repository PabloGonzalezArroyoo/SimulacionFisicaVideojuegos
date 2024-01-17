#include "TextSystem.h"
#include "../../structure/ecs/Manager.h"

// Recivir mensajes
void TextSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			if (state == MAINMENU_STATE) setMainMenuState();
			if (state == PLAY_STATE) setPlayState();
			else if (state == END_STATE) setEndState();
			break;
		case _m_USE_FUEL:
			updateFuel(m.fuel_data.fuel);
			break;
	}
}

// Update
void TextSystem::update(double t) {
	if (state == MAINMENU_STATE) flickerText(t);
	else if (state == PLAY_STATE) updateDistance(mngr->getHandler(_hdlr_JETPACK)->getPos().x);
}

// Hacer que el texto de inicio parpadee
void TextSystem::flickerText(double t) {
	elapsedTime += t;
	if (elapsedTime > 1.2) {
		texts[START] = "Press SPACE to start";
		elapsedTime = 0;
	}
	else if (elapsedTime > 0.6) texts[START] = "";
}

// Actualizar texto de distancia
void TextSystem::updateDistance(int x) {
	texts[DISTANCE] = "Distance: " + to_string(x / 10);
}

// Actualizar texto de combustible
void TextSystem::updateFuel(int fuel) {
	texts[FUEL] = "FUEL: " + to_string(fuel) + "%";
}

// Quitar textos
void TextSystem::removeTexts() {
	for (int i = 1; i < texts.size(); i++) texts[i] = "";
}

// Ajustar textos para el PlayState
void TextSystem::setPlayState() {
	// Quitar textos anteriores
	removeTexts();

	// Activar texto de distancia y combustible
	texts[DISTANCE] = "Distance: 0";
	texts[FUEL] = "FUEL: 100%";

	/*Vector3 cameraPos = mngr->getHandler(_hdlr_PENGUIN)->getPos() + Vector3(0.0, 100.0, -200.0);
	pointsUI = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(cameraPos + Vector3(10, 0, 20)),
		CreateShape(PxBoxGeometry(10, 1, 1)), NONE, Vector4(1, 1, 1, 1), 10);
	pointsUI->disableGravity();*/
}

void TextSystem::setMainMenuState() {
	// Quitar textos anteriores
	removeTexts();

	// Activar textos del menú
	texts[TITLE] = "[ FARBALL ]";
	texts[START] = "Press SPACE to start";
}

void TextSystem::setEndState() {
	// Quitar textos anteriores
	removeTexts();

	// Activar texto del final
	texts[END] = "Oh no! Te has chocado! Intentalo de nuevo!";
}