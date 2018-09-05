#include <stdio.h>

#include <stdbool.h>



#define mapHeight 21

#define mapWidth 80


int terminalHeight = 24;

int numberOfRooms = 5;

struct tile {
  int hardness;
  char value;
};

struct room {
  int x;
  int y;
  int width;
  int height;
};

struct tile map[mapHeight][mapWidth];

struct room rooms[5];


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

void placeRoom(int givenx, int giveny, int givenWidth, int givenHeight, int roomIndex){
  int i,j;

  for(i = giveny; i <= (giveny + givenHeight); ++i){
    for(j = givenx; j <= (givenx + givenWidth); ++j){
      rooms[roomIndex].x = givenx;
      rooms[roomIndex].y = giveny;
      rooms[roomIndex].width = givenWidth;
      rooms[roomIndex].height = givenHeight;
      map[i][j].hardness = 0;
      map[i][j].value = '.';
    }
  }

}

void sortAllRooms(){
  int i, j, minIndex;
  for(i = 0; i < 4; ++i){
    minIndex = i;
    for(j = i+1; j < 5; ++j){
      if(rooms[j].x < rooms[minIndex].x){
	struct room tempRoom = rooms[i];
	rooms[i] = rooms[j];
	rooms[j] = tempRoom;
      }
    }
  }
}

void addCorridors(int givenx1, int giveny1, int givenx2, int giveny2){
  int i, j, increment;

  if(giveny2 - giveny1 != 0){
    increment =  abs(giveny2 - giveny1)/(giveny2-giveny1);
  }

  for(i = giveny1; i !=  giveny2; i += increment){
    if(map[i][givenx1].value == ' '){
      map[i][givenx1].value = '#';
    }
  }

  if(givenx2 - givenx1 != 0){
    increment =  abs(givenx2 - givenx1)/(givenx2-givenx1);
  }
  for(j = givenx1; j != givenx2; j += increment){
    if(map[giveny2][j].value == ' '){
      map[giveny2][j].value = '#';
    }
  }
}

void placeCorridors(){
  sortAllRooms();
  int i, x1, x2, y1, y2;

  
  for(i = 0; i < 4; ++i){
    x1 = rooms[i].x;
    y1 = rooms[i].y;
    x2 = rooms[i+1].x;
    y2 = rooms[i+1].y;
    addCorridors(x1,y1,x2,y2);
  }

  x1 = rooms[4].x;
  y1 = rooms[4].y;
  x2 = rooms[0].x;
  y2 = rooms[0].y;
  addCorridors(x1,y1,x2,y2);
}


bool validRoom(int givenX, int givenY, int givenWidth, int givenHeight){
  int i, j;

  for(i = (givenY-1); i <= (givenY + givenHeight +1); ++i){
    for(j = (givenX-1); j <= (givenX + givenWidth +1); ++j){
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
      placeRoom(x, y, doorWidth, doorHeight, i);
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

  placeCorridors();

  printMap();
}
