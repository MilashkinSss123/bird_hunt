#include "Bird.h"

Bird::Bird(int screenWidth, int screenHeight)
    : GameObject(), alive(true), screenWidth(screenWidth),
      screenHeight(screenHeight) {
  position.x = rand() % screenWidth;
  position.y = 0;
}

void Bird::update() {

  if (rand() % 7 == 0) {
    position.y++;
  }
  if (position.y >= screenHeight) {
    alive = false;
  }
}

void Bird::draw(CHAR_INFO *buffer, int screenWidth, int screenHeight) const {
  if (alive) {
    int index = position.y * screenWidth + position.x;
    buffer[index].Char.AsciiChar = 'V';
    buffer[index].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
  }
}
