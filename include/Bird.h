#pragma once
#include "GameObject.h"

class Bird : public GameObject {
public:
  Bird();
  Bird(int, int);
  virtual void draw(CHAR_INFO *buffer, int screenWidth,
                    int screenHeight) const override;
  void update() override;
  bool alive;
  int screenWidth, screenHeight;
};
