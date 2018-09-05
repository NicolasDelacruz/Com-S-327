#include <stdio.h>
#include <stdbool.h>
#include <math.h>


//the variable mapHeight is an immutable variable that holds the value 21 that represents that height of map
#define mapHeight 21

//the variable mapWidth is an immutable variable that hold the value 80 that represents the width of the map
#define mapWidth 80

//the variable terminalHeight is the total height of the terminal
int terminalHeight = 24;

//the variable numberOfRooms represents the total number of rooms on the map
int numberOfRooms = 5;

//the struct tile is to represent each tile on the map
struct tile {
  int hardness;
  char value;
};

//the struct room is to represent a room
struct room {
  int x;
  int y;
  int width;
  int height;
};

//the array map is a 2D array that is made up of tile structs
struct tile map[mapHeight][mapWidth];

//the array rooms is an arra that is made up of room structs
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


//the function generateMap places the border of the map
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

//the function placeRoom places a room starting at given X & Y coordinates at a given height and width
//this function also adds the room to the rooms array
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

//the function sortAllRooms re-arranges the rooms by x-coordinates from lowest to greatest
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

//the function addCorridors adds the corridors to the map by adding the y then the x corridors
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

//the function placeCorridors sorts the array of rooms then iterates through all of the array -1 to add the corridors
//the function also connects the last room with the first one to finish the loop
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

//the function validRoom takes in the following ints: x,y, width, and height
//with these variables the function checks if placing a room with these parameters is valid
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

//the function generateAllRooms keeps attempting to place a room of random dimensions and location until it meets total number of rooms requirement
void generateAllRooms(){
  int doorWidth, doorHeight, x, y;
  int i;

  for(i = 0; i < numberOfRooms; ++i){
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

//the function generateRandomNum generates a random number between the low and high (both are available)
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

//the function printMap prints the entire map on the terminal
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
