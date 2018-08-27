#include <stdio.h>
#include <stdbool.h>

//The variable board is used to store all the tiles for the board
int board[5][5] = {{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}};

/*The variables col and row are for the possible moves the knight can make
 *1: Up 2, Left 1
 *2: Up 2, Right 1
 *3: Up 1, Right 2
 *4: Down 1, Right 2
 *5: Down 2, Right 1
 *6: Down 2, Left 1
 *7: Down 1, Left 2
 *8: Up 1, Left 2
 */
int col[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int row[8] = {1, 2, 2, 1, -1, -2, -2, -1};

//The variable tempCordinates is used to hold temporary cordinates
int tempCordinates[2];

//The variable visited is used to store all the tiles that have been visited on the board (not checked, the knight has to MOVE there not just to check it)
int visited[25];

//The variable tempVisited is used to store the temporary path the program is in
int tempVisited[25] = {0};

//The variable indexOfTempVisited is used to keep track of index for tempVisited
int indexOfTempVisited = 0;

//The variable boardSize is used to store the number of tiles in the board (used for counter in for-loop) (5)
int boardSize = 5;

//The variable board size is used to store the number of moves that are available (used for counter in for-loop) (8)
int numberOfMovesAvailable = 8;

//The variable currentLocation is used to keep track of the current location the knight is on the board
int currentLocation;

//--------------------------------------------------------------------------------------------------------------------------------------------------------


/*
 *The function copyArray is used to copy all values from arrToCopy to the array arrToPaste
 */
void copyArray(int arrToPaste[], int arrToCopy[]);

/*
 *The fillArray function fills the array, givenArray, with 0s.
 */
void fillArray(int givenArr[]);

/*
 *The function getLocation takes in an int, location, that represent a value 1-25 and returns the cordinates of the board that has the value.
 */
void getLocation(int location);

/*
 *The function inArray checks if the int, value, is within the int array, givenArray.
 */
bool inArray(int givenArray[], int value);

/*
 *The function validMove is used to check if the anticipated move is valid, or if it has already been done.
 */
bool validMove(int col, int row);

/*
 *The function tour is a recursive method that takes in the location and recursively gets all the paths for that location
 */
void tour(int location);

/*
 *The function printArray prints out the givenArray
 */
void printArray(int givenArray[]);

//-------------------------------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[]){

  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      currentLocation = board[i][j]; 
      tour(currentLocation);
      copyArray(visited, tempVisited);
      printArray(visited);
    }
    fillArray(visited);
    fillArray(tempVisited);
    indexOfTempVisited = 0;
    tempCordinates[0] = 0;
    tempCordinates[1] = 0;
  }

  return 0;
}


void copyArray(int arrToPaste[], int arrToCopy[]){
  int sizeOfGivenArray = sizeof(arrToPaste)/sizeof(arrToPaste[0]);
  int i;
  for(i = 0; i < sizeOfGivenArray; ++i){
    arrToPaste[i] = arrToCopy[i];
  }
}

void fillArray(int givenArr[]){
  int sizeOfGivenArray = sizeof(givenArr)/sizeof(givenArr[0]);
  int i;
  for(i = 0; i < sizeOfGivenArray; ++i){
    givenArr[i] = 0;
  }
}

void getLocation(int location){
  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      if(location == board[i][j]){
	tempCordinates[0] = i;
	tempCordinates[1] = j;
      }
    }
  }
}


bool inArray(int givenArray[], int value){
  int i;

  int sizeOfArray = sizeof(givenArray)/sizeof(givenArray[0]);

  for(i = 0; i < sizeOfArray; ++i){
    if(value == givenArray[i]){
      return true;
    }
  }
  return false;
}



void printArray(int givenArray[]){
  int i;

  for(i = 0; i < 25; ++i){
    printf("%d", givenArray[i]);
    printf("\t");
  }
  printf("\n");
}


void tour(int location){
  int i;

  for(i = 0; i < numberOfMovesAvailable; ++i){
    if(validMove(col[i], row[i])){
      tour(currentLocation);
    }
  }
}


bool validMove(int col, int row){
  getLocation(currentLocation);
  int newLocation = board[tempCordinates[0]+col][tempCordinates[0]+row];
  bool inArr = inArray(tempVisited, newLocation);

  if(newLocation > 0 && newLocation < 26 && !(inArr)){
    tempVisited[indexOfTempVisited] = newLocation;
    currentLocation = newLocation;
    indexOfTempVisited++;
    return true;
  }
  return false;
}
