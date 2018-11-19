#ifndef DUNGEON_H
# define DUNGEON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIELD_SIZE           10
#define NUM_MINES            3


class field {
 public:
 field() : map{0}, display_map{0}, game_over(0), num_mines(0), quit(0) {}
  char map[FIELD_SIZE][FIELD_SIZE];
  char display_map[FIELD_SIZE][FIELD_SIZE];
  int game_over;
  int num_mines;
  int quit;
};

void gen_field(field *f);
void init_field(field *f);

#endif
