#include <stdio.h>

#include <stdbool.h>



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

void placeRoom(int givenx, int giveny, int givenWidth, int givenHeight){
  int i,j;

  for(i = giveny; i <= (giveny + givenHeight); ++i){
    for(j = givenx; j <= (givenx + givenWidth); ++j){
      map[i][j].hardness = 0;
      map[i][j].value = '.';
    }
  }

}


bool validRoom(int givenX, int givenY, int givenWidth, int givenHeight){
  int i, j;

  int tempX = givenX;
  int tempY = givenY;

  if(givenY > 1){
    tempY -= 1;
  }

  if(givenX > 1){
    tempX -= 1;
  }

  for(i = tempY; i <= (tempY + givenHeight +1); ++i){
    for(j = tempX; j <= (tempX + givenWidth +1); ++j){
      if(map[i][j].value != ' '){
	return false;
      }
    }
  }
  return true;
}

void generateAllRooms(){
  int doorWidth, doorHeight, x, y;
  int i;

  for(i = 0; i < 5; ++i){
    doorWidth = generateRandomNum(3, 10);
    doorHeight = generateRandomNum(2,10);
    x = generateRandomNum(1,(mapWidth - doorWidth));
    y = generateRandomNum(1,(mapHeight - doorHeight));
    if(validRoom(x,y,doorWidth,doorHeight)){
      placeRoom(x, y, doorWidth, doorHeight);
    }
    else{
      i--;
    }
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
