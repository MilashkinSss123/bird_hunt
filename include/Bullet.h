#pragma once
#include "GameObject.h"

class Bullet : public GameObject {
public:
  Bullet(int, int);
  void update() override;
  virtual void draw(CHAR_INFO *buffer, int screenWidth,
                    int screenHeight) const override;
  bool active;
};
