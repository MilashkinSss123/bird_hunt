#include "Bullet.h"

Bullet::Bullet(int startX, int startY) : GameObject(), active(true) {
  position.x = startX;
  position.y = startY;
}

void Bullet::update() {
  position.y--;
  if (position.y < 0) {
    active = false;
  }
}

void Bullet::draw(CHAR_INFO *buffer, int screenWidth, int screenHeight) const {
  if (active) {
    int index = position.y * screenWidth + position.x;
    buffer[index].Char.AsciiChar = 'o';
    buffer[index].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
  }
}
