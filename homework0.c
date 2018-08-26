#include <stdio.h>
#include <stdbool.h>

//The variable board is used to store all the tiles for the board
int board[5][5] = [{1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20},{21,22,23,24,25}];

/*The variable possibleMoves is used to store all the different moves that the knight can make
 *1: Up 2, Left 1
 *2: Up 2, Right 1
 *3: Up 1, Right 2
 *4: Down 1, Right 2
 *5: Down 2, Right 1
 *6: Down 2, Left 1
 *7: Down 1, Left 2
 *8: Up 1, Left 2
 */
int possibleMoves = {1,2,3,4,5,6,7,8};

//The variable visited is used to store all the tiles that have been visited on the board (not checked, the knight has to MOVE there not just to check it)
int visited[25] = {0};

//The variable boardSize is used to store the number of tiles in the board (used for counter in for-loop)
int boardSize = sizeof(visited)/sizeof(visited[0]);

//The variable board size is used to store the number of moves that are available (used for counter in for-loop)
int numberOfMoves = sizeof(possibleMoves)/sizeof(possibleMoves[0]);

//The variable currentLocation is used to keep track of the current location the knight is on the board
int currentLocation;

/*
 *The function validMove is used to check if the anticipated move is valid, or if it has already been done.
 */
boolean validMove(int move, int location){

  int boardLocation[];
  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      if(location == boardSize[i][j]){
	boardLocation = {i,j};
      }
    }
  }

  if(tempLocation > 0 && tempLocation < 26){
    return true;
  }
  else{
    return false;
  }
}

int getTempLocation(int move, int location){
  int boardLocation[];
  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      if(location == boardSize[i][j]){
	boardLocation = {i,j};
      }
    }
  }
}


int nextMove(int move, int location[][]){
  currentLocation = location;
  return currentLocation;
}


void tour(int location){
  currentLocation = location;
  for(i = 0; i < numberOfMoves; ++i){
    if(validMove(numberOfMoves[i], currentLocation)){
      tour(nextMove(numberOfMoves[i], currentLocation));
    }
  }
}


int main(int argc, char const *argv[]){

  int i;
  for(i = 0; i < boardSize; ++i){
    tour(board[i]);
  }

  return 0;
}
