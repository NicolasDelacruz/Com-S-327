#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "field.h"

static void place_mines(field *f){
  int i, mine_x, mine_y;

  srand(time(NULL));

  for(i = 0; i < NUM_MINES; ++i){
    mine_x = rand() % (FIELD_SIZE - 1);
    mine_y = rand() % (FIELD_SIZE - 1);

    if(f->map[mine_y][mine_x] == 0){
      f->map[mine_y][mine_x] = '*';
      f->display_map[mine_y][mine_x] = '*';
      
    }else{
      i--;
    }

  }

}

void gen_field(field *f){
  int i, j;
  
  place_mines(f);
  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      if(f->display_map[i][j] != '*' ){
	f->display_map[i][j] = 'X';
      }
    }
  }
}

void init_field(field *f){
  //set everything to 0
  memset(f, sizeof(f), 0);

  //initialize variables;
  f->num_mines = NUM_MINES;
  f->quit = 0;
  f->game_over = 0;
}
