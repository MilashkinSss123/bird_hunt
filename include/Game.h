#pragma once
#include "Bird.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Gun.h"
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

class Game {

public:
  Game();
  ~Game();

  void run();
  void update();
  void draw();
  void processInput(char key);
  void checkCollisions();
  void swapBuffers();
  void clearBuffer();
  void drawToBuffer(int x, int y, const std::string &c);
  void displayHelp();

  std::vector<Bird> birds;
  Gun gun;

  int score;
  bool isRunning;
  bool isDrawing;
  std::thread gameThread;

  int screenWidth;
  int screenHeight;

  CHAR_INFO *frontBuffer;
  CHAR_INFO *backBuffer;
  HANDLE hConsoleOutput;
};
