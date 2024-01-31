#pragma once
#include "Bullet.h"
#include "GameObject.h"
#include <vector>

class Gun : public GameObject {
public:
  Gun();
  Gun(int, int);
  void shoot();
  virtual void draw(CHAR_INFO *buffer, int screenWidth,
                    int screenHeight) const override;
  virtual void update() override;
  std::vector<Bullet> bullets;
};
