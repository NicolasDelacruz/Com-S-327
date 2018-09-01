#include <stdio.h>

#define mapHeight 21

#define mapWidth 80


int terminalHeight = 24;

struct tile {
  int hardness;
  char value;
};

struct tile map[mapHeight][mapWidth];


/*
 * Requirements:
 * At least 5 doors
 * (Rooms): 
 * -minimum of 3 units (x-direction) and minimum of 2 units (y-direction)
 * -minimum of 1 unit (in x & y direction) of space between doors, they CANNOT overlap
 * 
 * (Symbols):
 * -Room = "."
 * -Corridor = "#"
 * -Rock = " "
 *
 * Corridors:
 * -Cannot extend into rooms
 * -Must connect all rooms together
 */

void generateMap(){
  int i, j;

  for(i = 0; i < mapHeight; ++i){
    for(j = 0; j < mapWidth; ++j){
      map[i][j].hardness = 0;


      if(i == 0 || i == (mapHeight -1)){
        map[i][j].value = '-';
      }
      else if(i < (mapHeight -1)){
	if(j == 0 || j == (mapWidth -1)){
	  map[i][j].value = '|';
	}
	else{
	  map[i][j].value = ' ';
	}
      }
    }
  }
}

int printMap(){
  int i, j;

  for(i = 0; i < mapHeight; ++i){
    for(j = 0; j < mapWidth; ++j){
      printf("%c", map[i][j].value);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
  printf("\n");
}

int main(int argc, char const *arfv[]){

  generateMap();
  printMap();
}
