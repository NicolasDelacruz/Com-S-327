#ifndef GRID_H
# define GRID_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GRID_WIDTH        7
#define GRID_HEIGHT       6


class grid {
 public:
 grid() : map{0}, game_over(0), quit(0) {}
  char map[GRID_HEIGHT][GRID_WIDTH];
  char game_end;
  int turn;
  int game_over;
  int quit;
};

void init_grid(grid *g);

#endif
