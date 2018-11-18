#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "field.h"

int main(int argc, char *argv[])
{
  field f;
  using namespace std;

  init_field(&f);
  gen_field(&f);

  char temp;

  int i, j;
  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      temp = f.display_map[i][j];
      cout << temp;
    }
    cout << endl;
  }


  /*
  io_display(&d);
  
  while ( !(game_over(&f)) && !f.quit) {
    do_moves(&d);
  }

  if(f.win){
    //display win
  } else {
    //display loss
  }
  */

  return 0;
}
