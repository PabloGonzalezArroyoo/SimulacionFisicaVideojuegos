#include "TextSystem.h"
#include "../../structure/ecs/Manager.h"

void TextSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			if (state == PLAY_STATE) setPlayState();
			break;
		/*case _m_PENGUIN_POS_UPDATE:
			updateDistance(m.penguin_pos_data.x);
			break;*/
	}
}

void TextSystem::update(double t) {
	if (state == MAINMENU_STATE) flickerText(t);
	else if (state == PLAY_STATE) updateDistance(mngr->getHandler(_hdlr_PENGUIN)->getPos().x);
}

void TextSystem::flickerText(double t) {
	elapsedTime += t;
	if (elapsedTime > 1.2) {
		texts[START] = "Press SPACE to start";
		elapsedTime = 0;
	}
	else if (elapsedTime > 0.6) texts[START] = "";
}

void TextSystem::updateDistance(int x) {
	texts[DISTANCE] = "Distance: " + to_string(x / 10);
}

void TextSystem::removeTexts() {
	for (int i = 1; i < texts.size() - 1; i++) texts[i] = "";
}

void TextSystem::setPlayState() {
	// Activar texto de distancia
	texts[DISTANCE] = "Distance: 0";

	/*Vector3 cameraPos = mngr->getHandler(_hdlr_PENGUIN)->getPos() + Vector3(0.0, 100.0, -200.0);
	pointsUI = new RigidBody(mngr->getPhysics(), mngr->getScene(), PxTransform(cameraPos + Vector3(10, 0, 20)),
		CreateShape(PxBoxGeometry(10, 1, 1)), NONE, Vector4(1, 1, 1, 1), 10);
	pointsUI->disableGravity();*/
}