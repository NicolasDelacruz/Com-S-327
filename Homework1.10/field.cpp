#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "field.h"


static void fill_display_map(field *f){
  int i, j;
  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      f->display_map[i][j] = 'X';
    }
  }
}


static void place_mines(field *f){
  int i, mine_x, mine_y;

  i = 0;

  srand(time(NULL));

  while(i < NUM_MINES){
    mine_x = rand() % (FIELD_SIZE - 1);
    mine_y = rand() % (FIELD_SIZE - 1);

    if(f->map[mine_y][mine_x] == 0){
      f->map[mine_y][mine_x] = '*';
      i++;
    }
  }
}


static int get_number_mines(int y_cord, int x_cord, field *f){
  int n_mines, min_x, min_y, max_x, max_y;

  n_mines = 0;
  
  if(y_cord - 1 >= 0){
    min_y = y_cord - 1;
  }else{
    min_y = 0;
  }
  
  if(x_cord - 1 >= 0){
    min_x = x_cord - 1;
  }else{
    min_x = 0;
  }

  if(y_cord + 1 < FIELD_SIZE){
    max_y = y_cord + 1;
  }else{
    min_y = 9;
  }

  if(x_cord + 1 < FIELD_SIZE){
    max_x = x_cord + 1;
  }else{
    min_x = 9;
  }

  //N
  if(f->map[min_y][x_cord] == '*'){
    n_mines++;
  }

  //NE
  if(f->map[min_y][max_x] == '*'){
    n_mines++;
  }

  //E
  if(f->map[y_cord][max_x] == '*'){
    n_mines++;
  }

  //SE
  if(f->map[max_y][max_x] == '*'){
    n_mines++;
  }

  //S
  if(f->map[max_y][x_cord] == '*'){
    n_mines++;
  }
  
  //SW
  if(f->map[max_y][min_x] == '*'){
    n_mines++;
  }

  //W
  if(f->map[y_cord][min_x] == '*'){
    n_mines++;
  }

  //NW
  if(f->map[min_y][min_x] == '*'){
    n_mines++;
  }

  return n_mines;
}


static void place_numbers(field *f){
  int i,j, num_mines;

  char num;

  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      if(f->map[i][j] != '*'){
	num_mines = get_number_mines(i, j, f);
	num = num_mines +'0';
	f->map[i][j] = num;
      }
    }
  }
}


void gen_field(field *f){
  place_mines(f);
  place_numbers(f);

  fill_display_map(f);
  
}


void init_field(field *f){
  //set everything to 0
  //memset(f, sizeof(f), 0);

  //initialize variables;
  f->num_mines = NUM_MINES;
  f->quit = 0;
  f->game_over = 0;
}
