#include "Gun.h"
#include "GameObject.h"
#include <algorithm>

Gun::Gun() : GameObject(){};

Gun::Gun(int x, int y) : GameObject(x, y){};

void Gun::shoot() { bullets.push_back(Bullet(position.x, position.y - 1)); }

void Gun::update() {
  for (auto &bullet : bullets) {
    bullet.update();
  }

  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](Bullet &b) { return !b.active; }),
                bullets.end());
}

void Gun::draw(CHAR_INFO *buffer, int screenWidth, int screenHeight) const {
  int index = position.y * screenWidth + position.x;
  buffer[index].Char.AsciiChar = '1';
  buffer[index].Attributes =
      FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
}
