#include "TextSystem.h"
string title_text = "FARBALL";

void TextSystem::initSystem() {
	drawText("FARBALL", glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void TextSystem::update(double t) {

}