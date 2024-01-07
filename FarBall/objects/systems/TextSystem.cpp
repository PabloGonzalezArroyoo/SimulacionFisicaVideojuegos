#include "TextSystem.h"

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

void TextSystem::removeTexts() {
	for (int i = 1; i < texts.size(); i++) texts[i] = "";
}