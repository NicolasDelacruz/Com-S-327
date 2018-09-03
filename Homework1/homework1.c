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
      map[i][j].hardness = 255;

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

void generateDoor(){
  int doorWidth = generateRandomNum(3, 10);
  int doorHeight = generateRandomNum(2,10);
  int x = generateRandomNum(1,(mapWidth - doorWidth));
  int y = generateRandomNum(1,(mapHeight - doorHeight));

  int i,j;

  for(i = y; i <= (y + doorHeight); ++i){
    for(j = x; j <= (x + doorWidth); ++j){
      map[i][j].hardness = 0;
      map[i][j].value = '.';
    }
  }

}

void generateAllRooms(){
  int i;

  for(i = 0; i < 5; ++i){
    generateDoor();
  }
}

int generateRandomNum(int low, int high){
  int lower = low;
  int upper = high;

  int randomNumber = 0;

  //srand(time(NULL)); //Seeding with current time

  randomNumber = rand() % upper;

  if(randomNumber < lower)
  {
    randomNumber += lower;
  }
  return randomNumber;
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
  srand(time(NULL)); //Seeding with current time


  generateMap();

  generateAllRooms();

  printMap();
}
