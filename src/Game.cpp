#define NOMINMAX
#include "Game.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include <conio.h>
bool keyHit() { return _kbhit(); }
char getChar() { return _getch(); }

Game::Game() : isRunning(true), score(0), isDrawing(true) {
  srand(static_cast<unsigned int>(time(nullptr)));
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
  screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  screenWidth /= 3;
  screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  gun = Gun(screenWidth / 2, screenHeight - 1);
  frontBuffer = new CHAR_INFO[screenWidth * screenHeight];
  backBuffer = new CHAR_INFO[screenWidth * screenHeight];
}

Game::~Game() {
  delete[] frontBuffer;
  delete[] backBuffer;
}

void Game::processInput(char key) {
  switch (key) {
  case 'a':
    gun.position.x = std::max(0, gun.position.x - 1);
    break;
  case 'd':
    gun.position.x = std::min(screenWidth - 1, gun.position.x + 1);
    break;
  case ' ':
    gun.shoot();
    break;
  case 'h':
  case '?':
    displayHelp();
    break;
  default:
    break;
  }
}
void Game::displayHelp() {
  isDrawing = false;
  system("cls");
  std::string helpMessage = "Help:\n";
  helpMessage += "Press 'a' to move left\n";
  helpMessage += "Press 'd' to move right\n";
  helpMessage += "Press ' ' to shoot\n";
  helpMessage += "Press 'h' or '?' to display this help\n";
  helpMessage += "Game objective: Shoot as many birds as possible\n";
  helpMessage += "Press any key to continue\n";

  clearBuffer();
  int x = 0;
  int y = screenHeight / 2;

  for (auto &c : helpMessage) {
    if (c == '\n') {
      y++;
      x = 0;
    } else {
      drawToBuffer(x, y, &c);
      x++;
    }
  }
  COORD bufferSize = {static_cast<SHORT>(screenWidth),
                      static_cast<SHORT>(screenHeight)};
  COORD bufferCoord = {0, 0};
  SMALL_RECT writeRegion = {0, 0, static_cast<SHORT>(screenWidth - 1),
                            static_cast<SHORT>(screenHeight - 1)};
  WriteConsoleOutput(hConsoleOutput, backBuffer, bufferSize, bufferCoord,
                     &writeRegion);
  getChar();
  isDrawing = true;
}

void Game::update() {
  gun.update();
  for (auto &bird : birds) {
    bird.update();
  }
  birds.erase(std::remove_if(birds.begin(), birds.end(),
                             [](Bird &b) { return !b.alive; }),
              birds.end());
  if (rand() % 37 == 0) {
    birds.push_back(Bird(screenWidth, screenHeight));
  }
}

void Game::checkCollisions() {
  for (auto &bullet : gun.bullets) {
    for (auto &bird : birds) {
      if (bullet.active && bird.alive && (bullet.position == bird.position)) {
        bullet.active = false;
        bird.alive = false;
        score++;
      }
    }
  }
  if (std::any_of(gun.bullets.begin(), gun.bullets.end(),
                  [](const Bullet &b) { return b.position.y <= 0; })) {
    system("cls");
    isRunning = false;
    isDrawing = false;
    std::cout << "You lost! Score is " << score << std::endl;
    _getch();
  }
}
void Game::swapBuffers() {
  CHAR_INFO *temp = frontBuffer;
  frontBuffer = backBuffer;
  backBuffer = temp;

  COORD bufferSize = {static_cast<SHORT>(screenWidth),
                      static_cast<SHORT>(screenHeight)};
  COORD bufferCoord = {0, 0};
  SMALL_RECT writeRegion = {0, 0, static_cast<SHORT>(screenWidth - 1),
                            static_cast<SHORT>(screenHeight - 1)};
  WriteConsoleOutput(hConsoleOutput, frontBuffer, bufferSize, bufferCoord,
                     &writeRegion);
}
void Game::clearBuffer() {
  for (int i = 0; i < screenWidth * screenHeight; ++i) {
    backBuffer[i].Char.AsciiChar = ' ';
    backBuffer[i].Attributes = 0;
  }
}
void Game::drawToBuffer(int x, int y, const std::string &c) {
  if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
    backBuffer[y * screenWidth + x].Char.AsciiChar = c[0];
    backBuffer[y * screenWidth + x].Attributes =
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
  }
}

void Game::draw() {
  clearBuffer();

  gun.draw(backBuffer, screenWidth, screenHeight);
  for (const Bullet &bullet : gun.bullets)
    bullet.draw(backBuffer, screenWidth, screenHeight);
  for (const Bird &bird : birds)
    bird.draw(backBuffer, screenWidth, screenHeight);
  int i = 0;
  auto str = std::string("SCORE:");
  str += std::to_string(score);
  for (auto &c : str) {
    drawToBuffer(i, 0, &c);
    i++;
  }
  swapBuffers();
}

void Game::run() {
  using namespace std::chrono;
  const int FPS = 17;
  const milliseconds frameDelay = duration_cast<milliseconds>(1s) / FPS;

  gameThread = std::thread([&]() {
    steady_clock::time_point frameStart;
    milliseconds frameTime;

    while (isRunning) {
      while (isDrawing) {
        frameStart = steady_clock::now();

        update();
        checkCollisions();
        draw();

        frameTime =
            duration_cast<milliseconds>(steady_clock::now() - frameStart);

        if (frameDelay > frameTime) {
          std::this_thread::sleep_for(frameDelay - frameTime);
        }

        if (score >= 10) {
          isRunning = false;
          isDrawing = false;
          std::cout << "Congratulations! You won! Score is " << score
                    << std::endl;
          _getch();
        }
      }
      std::this_thread ::sleep_for(std::chrono::seconds(1));
    }
  });

  while (isRunning) {
    if (keyHit()) {
      char key = getChar();
      processInput(key);
    }
  }

  gameThread.join();
}
