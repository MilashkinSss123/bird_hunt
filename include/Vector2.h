#pragma once

#include <cstdlib>
class Vector2 {
public:
  int x, y;

  Vector2(int x = 0, int y = 0) : x(x), y(y) {}
  bool operator==(const Vector2 &other) const {
    /* return x == other.x && y == other.y; */
    /* return abs(x - other.x) <= 1 && abs(y - other.y) <= 1; */
    return abs(x - other.x) <= 1 && y == other.y;
  }
};
