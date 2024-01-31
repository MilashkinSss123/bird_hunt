
#include "Game.h"
#include <iostream>

int main() {
  char choice;
  std::cout << "Welcome to Bird Hunt!" << std::endl;
  std::cout << "While playing, you can press h or ? to get help menu.\n";
  std::cout << "Press 's' to start the game or 'q' to quit: ";
  std::cin >> choice;

  if (choice == 's') {
    system("cls");
    Game game;
    game.run();
  } else if (choice == 'q') {
    std::cout << "Exiting the game." << std::endl;
  } else {
    std::cout << "Invalid input. Exiting the game." << std::endl;
  }

  return 0;
}
