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
int rowMoves[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
int colMoves[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

//The variable tempCordinates is used to hold cordinates of current position
//[row, col]
int currentCordinates[2];

//The variable visitedIndex is used to store the temporary path the program is in
int visitedIndex = 0;

//The variable visited is used to store all the tiles that have been visited on the board (not checked, the knight has to MOVE there not just to check it)
int visited[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//The variable boardSize is used to store the number of tiles in the board (used for counter in for-loop) (5)
int boardSize = 5;

//The variable board size is used to store the number of moves that are available (used for counter in for-loop) (8)
int numberOfMoves = 8;

int numberOfSolutions = 0;

int s = 0;

void printArray(int givenArr[]){
  int i;
  for(i = 0; i < 24; ++i){
    printf("%d ", givenArr[i]); 
  }
  numberOfSolutions++;
  printf("%d", numberOfSolutions);
  printf("\n");
  // printf("printing solution ");
  // printf("%d", s);
  // printf("\n");
}

void updateCordinates(int value){
  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      if(board[i][j] == value){
	currentCordinates[0] = i;//row
	currentCordinates[1] = j;//col
      }
    }
  }
}

bool inArray(int givenValue){
  int i;
  for(i = 0; i < 25; ++i){
    if(visited[i] == givenValue){
      return true;
    }
  }
    return false;
}


void tour(int tempRow, int tempCol){
  int i;

  //Adding the new value to visited
  visited[visitedIndex] = board[tempRow][tempCol];
  updateCordinates(visited[visitedIndex]);
  visitedIndex++;


  //checking if there is a solution
  if(visited[24] != 0){
    s ++;
    printArray(visited);
    updateCordinates(visited[visitedIndex-1]);
    visitedIndex --;
    visited[visitedIndex] = 0;
    return;
  }

  for(i = 0; i < numberOfMoves; ++i){
    updateCordinates(visited[visitedIndex-1]);
    int nextRow = currentCordinates[0] + rowMoves[i];
    int nextCol = currentCordinates[1] + colMoves[i];
    if(nextCol >= 0 && nextCol < boardSize && nextRow >= 0 && nextRow < boardSize && !(inArray(board[nextRow][nextCol]))){
      tour(nextRow, nextCol);
    }
  }

  //backtracking
  updateCordinates(visited[visitedIndex-1]);
  visitedIndex --;
  visited[visitedIndex] = 0;

}

void resetArray(){
  int i;
  for(i = 0; i < 25; ++i){
    visited[i] = 0;
  }
}


int main(int argc, char const *argv[]){

  int i, j;
  for(i = 0; i < boardSize; ++i){
    for(j = 0; j < boardSize; ++j){
      currentCordinates[0] = i;//row
      currentCordinates[1] = j;//col
      visitedIndex = 0;
      resetArray();
      tour(currentCordinates[0],currentCordinates[1]);
    }
  }

  return 0;
}
