#pragma once
#include "Vector2.h"
#include <memory>
#include <windows.h>

class GameObject {
public:
  Vector2 position;

  GameObject() : position(){};
  GameObject(int x, int y) : position(x, y){};

  virtual void update() = 0;
  virtual void draw(CHAR_INFO *buffer, int screenWidth,
                    int screenHeight) const = 0;
};
