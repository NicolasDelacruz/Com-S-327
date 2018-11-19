#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "field.h"
#include "io.h"

int main(int argc, char *argv[])
{
  field f;
  using namespace std;


  int i,j;
  char temp;

  init_field(&f);
  gen_field(&f);

  io_init_terminal();

  //io_display(&f);

  for(i = 0; i < FIELD_SIZE; ++i){
    for(j = 0; j < FIELD_SIZE; ++j){
      temp = f.map[i][j];
      if(temp == '\0'){
	cout << ' ';
      }else {
	cout << temp;
      }
    }
    cout << endl;
  }


  /*  
  while ( !(game_over(&f)) && !f.quit) {
    io_handle_input(&d);
  }

  if(f.win){
    //display win
  } else {
    //display loss
  }
  */

  return 0;
}
