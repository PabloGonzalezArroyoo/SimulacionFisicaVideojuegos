#include "TextSystem.h"
#include "../../structure/ecs/Manager.h"

void TextSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE:
			state = m.state_data.st;
			if (state == PLAY_STATE) setPlayState();
			break;
		case _m_PENGUIN_POS_UPDATE:
			updateDistance(m.penguin_pos_data.x);
			break;
	}
}

void TextSystem::update(double t) {
	if (state == MAINMENU_STATE) flickerText(t);
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
	texts[DISTANCE] = "Distance: " + to_string(x);
}

void TextSystem::removeTexts() {
	for (int i = 1; i < texts.size() - 1; i++) texts[i] = "";
}

void TextSystem::setPlayState() {
	texts[DISTANCE] = "Distance: 0";
}