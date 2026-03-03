#pragma once
#include <string>
#include <vector>


struct Level {

  // MEMBERS:
     int   levelNumber;       // 1, 2, 3, ...
     int   boardWidth;        // number of columns (e.g. 20)
     int   boardHeight;       // number of rows    (e.g. 20)
     int   obstacleCount;     // how many stones to spawn
     int   initialSnakeLen;   // how long the snake starts
     int   tickIntervalMs;    // milliseconds between game ticks
                              //   smaller = faster = harder

    // HINT FOR LATER (word-game extension):
    //   We will add something like:
    //     std::vector<std::string> wordList;
    //     std::vector<std::string> clueList;
    //   For now, leave them commented out.


  // TODO (OPTIONAL): add static factory functions
  //   static Level easy();
  //   static Level medium();
  //   static Level hard();
};
