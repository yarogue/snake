#include "GameEngine.hpp"
#include "Level.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  srand(time(nullptr)); // Seed random — different layout every run

  std::cout << "=== SNAKE GAME ===" << std::endl;
  std::cout << "Select level:  " << std::endl;
  std::cout << "  1. Easy      " << std::endl;
  std::cout << "  2. Medium    " << std::endl;
  std::cout << "  3. Hard      " << std::endl;
  std::cout << "Enter choice:(1-3)" << std::endl;

  int choice;
  std::cin >> choice;

  Level level;
  switch (choice) {
  case 1:
    level = Level{1, 40, 20, 5, 3, 200}; // EASY
    break;
  case 2:
    level = Level{2, 40, 20, 10, 3, 130}; // MEDIUM
    break;
  case 3:
    level = Level{3, 40, 20, 18, 3, 70}; // HARD
    break;
  default:
    std::cout << "Invalid level choice." << std::endl;
    level = Level{1, 40, 20, 5, 3, 200}; // Wrong input punishment EASY
    break;
  }

  GameEngine engine = GameEngine::create(level);
  engine.run();

  return 0;
}