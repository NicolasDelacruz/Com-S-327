#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "grid.h"

void init_grid(grid *g){
  //set everything to 0
  memset(g->map, sizeof(g->map), 0);

  //initialize variables;
  g->turn = 1;
  g->quit = 0;
  g->game_over = 0;
  g->game_end = 'z';
}
