#include "c4lib.h"
#include <iostream>
using namespace std;


// Prototype internal helper functions
/**
* @brief returns the smallest y coordinate that is BLANK in
*        column x or -1 if no location is BLANK
*/
int findYValue(BoardValue** board, int ydim, int x);




// ------------------------------------------------------------
// Global variabes - the ONLY we allow in this program


// converts integer player value: 0 or 1 to appropriate enum
enum BoardValue playerToValue[2] = {RED, YELLOW};


// ----------------------------------------------------------------------




// Helper function
int findYValue(BoardValue** board, int ydim, int x)
{
 // You complete
 bool fullcolumn = true;
 if(x >= 0){   //checks against negative x values that are invalid inputs
   for(int i=0; i < ydim; i++){
     if(board[i][x] == BLANK){   //checks to see if the board is full in the chosen column
     fullcolumn = false;
       return i;   //if the column is not full returns the value of the first open row in that column
       break;
     }
   }
 }
 if(fullcolumn){   //returns -1 if the column is full
   return -1;
 }
}


BoardValue** allocateBoard(int ydim, int xdim)
{
 // You complete
 BoardValue **board = new BoardValue*[ydim];   //allocates memory in the heap
 for(int i=0; i < ydim; i++){    //creates a board/2D array of given size
   board[i] = new BoardValue[xdim];
 }
 return board;
}
void deallocateBoard(BoardValue** board, int ydim)
{
 // You complete
 for(int i=0; i < ydim; i++){    //deletes/deallocates the allocated board
   delete [] board[i];
 }
 delete [] board;
}


void printBoard(BoardValue** board, int ydim, int xdim)
{
 // Complete - Do not alter
 const char* boardToString[] = { "\U000026ab", "\U0001F534", "\U0001F7E1" };
                                 //  "⚫",          "🔴",         "🟡"}
 for(int y = ydim-1; y >= 0; y--){
   for(int x = 0; x < xdim; x++) {
     cout << boardToString[(int)board[y][x]] << " ";
   }
   cout << endl;
 }
 cout << endl;
}


bool getNextHumanInput(
 BoardValue** board,
 int ydim, int xdim,
 int *y, int *x,
 int currentPlayer)
{
 // You complete
 bool badxinput = true;    //assumes the x input is invalid at the start
 cin >> *x;
 if(*x < xdim){    //checks to see if given input for x is valid
   *y = findYValue(board, ydim, *x);   //finds the first open row in x column
   if(*y == -1){   //checks to see if the column is full
     badxinput = true;   //confirms invalid input
   }
   else{   //if it is a valid input then the board gets udpated so that the player's piece can get dropped in the chosen column
     board[*y][*x] = playerToValue[currentPlayer];
     badxinput = false;      //confirms that the input is valid
   }
 }
 return badxinput;   //returns whether the input was valid or not
}


bool hasWon(
 BoardValue** board,
 int ydim, int xdim,
 int sy, int sx,
 int currentPlayer)
{
 // Keep, modify, or delete these as you desire
 // You complete
 bool win = false;   //assumes there has not been a winner yet
 for(int i=0; i < xdim; i++){    //scans the whole board to see if there is a winner in the vertical direction
   for(int j=3; j < ydim; j++){
     if((board[j][i] == playerToValue[currentPlayer]) && (board[j-1][i] == playerToValue[currentPlayer]) && (board[j-2][i] == playerToValue[currentPlayer]) && (board[j-3][i] == playerToValue[currentPlayer])){
       win = true;
       break;
     }
   }
   if(win){
     break;
   }
 }
 for(int i=0; i < ydim; i++){    //checks the whole board to see if there is a winner in the horizontal direction
   for(int j=3; j < xdim; j++){
     if((board[i][j] == playerToValue[currentPlayer]) && (board[i][j-1] == playerToValue[currentPlayer]) && (board[i][j-2] == playerToValue[currentPlayer]) && (board[i][j-3] == playerToValue[currentPlayer])){
       win = true;
       break;
     }
   }
   if(win){
     break;
   }
 }
 for(int i=3; i < ydim; i++){    //checks the whole board to see if there is a winner in the bottom left totop right diagonal direction
   for(int j=3; j < xdim; j++){
     if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j-1] == playerToValue[currentPlayer]) && (board[i-2][j-2] == playerToValue[currentPlayer]) && (board[i-3][j-3] == playerToValue[currentPlayer])){
       win = true;
       break;
     }
   }
   if(win){
     break;
   }
 }
 for(int i=3; i < ydim; i++){    //checks the whole board to see if there is a winner in the other diagonal direction
   for(int j=0; j < xdim-3; j++){
     if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j+1] == playerToValue[currentPlayer]) && (board[i-2][j+2] == playerToValue[currentPlayer]) && (board[i-3][j+3] == playerToValue[currentPlayer])){
       win = true;
       break;
     }
   }
   if(win){
     break;
   }
 }
return win;   //returns whether there is a winner or not
}


bool isDraw(
 BoardValue** board,
 int ydim, int xdim)
{
 // You complete
 bool fullboard = true;
 for(int i=0; i < xdim; i++){    //checks to see if the board is full or not
   if(board[ydim-1][i] == BLANK){
     fullboard = false;   //confirms the board is not full
     break;    
   }
 }
 return fullboard;     //returns whether or not the board is full endining in a draw
}






bool getUserAIInput(
 BoardValue** board,
 int ydim, int xdim,
 int *y, int *x,
 int currentPlayer)
{
 // You complete
 // Check if the current player can win
 int oppplayer;    //finds the opposing player
 bool notplaced = true;
 if(currentPlayer == 0){
   oppplayer = 1;
 }
 else if(currentPlayer == 1){
   oppplayer = 0;
 }
 for(int i=0; i < xdim; i++){    //scans the whole board to see if it can win vertically
   for(int j=3; j < ydim; j++){
     if((board[j][i] == BLANK) && (board[j-1][i] == playerToValue[currentPlayer]) && (board[j-2][i] == playerToValue[currentPlayer]) && (board[j-3][i] == playerToValue[currentPlayer])){
       board[j][i] = playerToValue[currentPlayer];
       notplaced = false;
       break;
     }
   }
   if(notplaced == false){
     break;
   }
 }
 if(notplaced){ 
   for(int i=0; i < ydim; i++){    //checks the whole board to see if it can win horizontally
     for(int j=3; j < xdim; j++){
       if((board[i][j] == BLANK) && (board[i][j-1] == playerToValue[currentPlayer]) && (board[i][j-2] == playerToValue[currentPlayer]) && (board[i][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i][j-1] == BLANK) && (board[i][j-2] == playerToValue[currentPlayer]) && (board[i][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j-1) == i)){
         board[i][j-1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i][j-1] == playerToValue[currentPlayer]) && (board[i][j-2] == BLANK) && (board[i][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j-2) == i)){
         board[i][j-2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i][j-1] == playerToValue[currentPlayer]) && (board[i][j-2] == playerToValue[currentPlayer]) && (board[i][j-3] == BLANK) && (findYValue(board, ydim, j-3) == i)){
         board[i][j-3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){    //checks the whole board to see if it could win in the bottom left totop right diagonal direction
     for(int j=3; j < xdim; j++){
       if((board[i][j] == BLANK) && (board[i-1][j-1] == playerToValue[currentPlayer]) && (board[i-2][j-2] == playerToValue[currentPlayer]) && (board[i-3][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j-1] == BLANK) && (board[i-2][j-2] == playerToValue[currentPlayer]) && (board[i-3][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j-1) == i-1)){
         board[i-1][j-1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j-1] == playerToValue[currentPlayer]) && (board[i-2][j-2] == BLANK) && (board[i-3][j-3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j-2) == i-2)){
         board[i-2][j-2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j-1] == playerToValue[currentPlayer]) && (board[i-2][j-2] == playerToValue[currentPlayer]) && (board[i-3][j-3] == BLANK) && (findYValue(board, ydim, j-3) == i-3)){
         board[i-3][j-3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){    //checks the whole board to see if it could win in the other diagonal direction
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == BLANK) && (board[i-1][j+1] == playerToValue[currentPlayer]) && (board[i-2][j+2] == playerToValue[currentPlayer]) && (board[i-3][j+3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j+1] == BLANK) && (board[i-2][j+2] == playerToValue[currentPlayer]) && (board[i-3][j+3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j+1) == i-1)){
         board[i-1][j+1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j+1] == playerToValue[currentPlayer]) && (board[i-2][j+2] == BLANK) && (board[i-3][j+3] == playerToValue[currentPlayer]) && (findYValue(board, ydim, j+2) == i-2)){
         board[i-2][j+2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[currentPlayer]) && (board[i-1][j+1] == playerToValue[currentPlayer]) && (board[i-2][j+2] == playerToValue[currentPlayer]) && (board[i-3][j+3] == BLANK) && (findYValue(board, ydim, j+3) == i-3)){
         board[i-3][j+3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 } 
 // Check if we need to block
 //  We can greedily play the first blocking location since
 //  if they can win in multiple ways it does not matter which
 //  we choose.
 if(notplaced){
   for(int i=0; i < xdim; i++){    //scans the whole board to see if it needs to block vertically
     for(int j=3; j < ydim; j++){
       if((board[j][i] == BLANK) && (board[j-1][i] == playerToValue[oppplayer]) && (board[j-2][i] == playerToValue[oppplayer]) && (board[j-3][i] == playerToValue[oppplayer])){
         board[j][i] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){ 
   for(int i=0; i < ydim; i++){    //checks the whole board to see if it needs to block horizontally
     for(int j=3; j < xdim; j++){
       if((board[i][j] == BLANK) && (board[i][j-1] == playerToValue[oppplayer]) && (board[i][j-2] == playerToValue[oppplayer]) && (board[i][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i][j-1] == BLANK) && (board[i][j-2] == playerToValue[oppplayer]) && (board[i][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j-1) == i)){
         board[i][j-1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i][j-1] == playerToValue[oppplayer]) && (board[i][j-2] == BLANK) && (board[i][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j-2) == i)){
         board[i][j-2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=0; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i][j-1] == playerToValue[oppplayer]) && (board[i][j-2] == playerToValue[oppplayer]) && (board[i][j-3] == BLANK) && (findYValue(board, ydim, j-3) == i)){
         board[i][j-3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){    //checks the whole board to see if it needs to block in the bottom left totop right diagonal direction
     for(int j=3; j < xdim; j++){
       if((board[i][j] == BLANK) && (board[i-1][j-1] == playerToValue[oppplayer]) && (board[i-2][j-2] == playerToValue[oppplayer]) && (board[i-3][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j-1] == BLANK) && (board[i-2][j-2] == playerToValue[oppplayer]) && (board[i-3][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j-1) == i-1)){
         board[i-1][j-1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j-1] == playerToValue[oppplayer]) && (board[i-2][j-2] == BLANK) && (board[i-3][j-3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j-2) == i-2)){
         board[i-2][j-2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=3; j < xdim; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j-1] == playerToValue[oppplayer]) && (board[i-2][j-2] == playerToValue[oppplayer]) && (board[i-3][j-3] == BLANK) && (findYValue(board, ydim, j-3) == i-3)){
         board[i-3][j-3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){    //checks the whole board to see if needs to block in the other diagonal direction
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == BLANK) && (board[i-1][j+1] == playerToValue[oppplayer]) && (board[i-2][j+2] == playerToValue[oppplayer]) && (board[i-3][j+3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j) == i)){
         board[i][j] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j+1] == BLANK) && (board[i-2][j+2] == playerToValue[oppplayer]) && (board[i-3][j+3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j+1) == i-1)){
         board[i-1][j+1] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j+1] == playerToValue[oppplayer]) && (board[i-2][j+2] == BLANK) && (board[i-3][j+3] == playerToValue[oppplayer]) && (findYValue(board, ydim, j+2) == i-2)){
         board[i-2][j+2] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 if(notplaced){
   for(int i=3; i < ydim; i++){   
     for(int j=0; j < xdim-3; j++){
       if((board[i][j] == playerToValue[oppplayer]) && (board[i-1][j+1] == playerToValue[oppplayer]) && (board[i-2][j+2] == playerToValue[oppplayer]) && (board[i-3][j+3] == BLANK) && (findYValue(board, ydim, j+3) == i-3)){
         board[i-3][j+3] = playerToValue[currentPlayer];
         notplaced = false;
         break;
       }
     }
     if(notplaced == false){
       break;
     }
   }
 }
 // Add any other logic for how to choose a location to play
 // if neither case above occurs
 if(notplaced){
   for(int i=0; i < xdim; i++){
     int j = findYValue(board, ydim, i);
     if(j != -1){
       board[j][i] = playerToValue[currentPlayer];
       break;
     }
   }
 }
 return false;
}


// Complete - Do not alter
bool getRandomAIInput(
 BoardValue** board,
 int ydim, int xdim,
 int *y, int *x,
 int currentPlayer)
{
 // Allocate variable size array (we don't know xdim when we compile)
 int* possible = new int[xdim];
 int numX = 0;
 bool error = true;
 // find all the possible columns with a blank
 for(int i = 0; i < xdim; i++){
   if(board[ydim-1][i] == BLANK){
     possible[numX++] = i;
   }
 }
 // If at least 1 column has a blank
 if(numX != 0){
   // Choose one column
   *x = possible[rand()%numX];
   *y = findYValue(board, ydim, *x);
   board[*y][*x] = playerToValue[currentPlayer];
   error = false; 
 }
 delete [] possible;
 return error;
}
