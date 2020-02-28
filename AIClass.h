/******************************************************************************
 Student Name:      Roberto Shu
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         AIClass.h
******************************************************************************/
#ifndef _AICLASS_H_
#define _AICLASS_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "ShipClass.h"
#include "GUIGLOBALCONSTANTS.h"


using namespace std;
 
class AIClass
{
  private:
  	// boolean to keep track if a ship has been found 
    bool newShipFound;
    // boolean to keep track if direction of ship is known
    bool foundDirec;
    // int to store the X and Y coordinates of the last turn. Will be used to 
    // determine what is the next smart move.
    int lastTurnXCord;
    int lastTurnYCord;
    // int to store the X and Y coordinates of the location a ship was found
    // for the first time
    int foundShipAtYCord;
    int foundShipAtXCord; 
    
    // 2D array of int where the AI will track where he has dropped bombs during 
    // the game.
    int bombsMap[NUM_MAX_ROWS][NUM_MAX_COLS];
    
    // 2D array of int where the AI will track where he has placed ships
    int shipsMap[NUM_MAX_ROWS][NUM_MAX_COLS];
    
    // int parameter that can either be 0 = up,1 = right ,2 = down,3 = left. 
    int shipDirec;
    // strings to identify the next and last move. There are only 4 possible 
    // moves. The string value for each move is declared in the global constant.
    string lastMove;
    string nextMove;
   
    
  public:
    // Function: initAI - initializes the AI. It sets the bombs map and ships 
    // map to empty space symbols. These maps will let the AI track what he has 	
    // been doing. It will also initialize to false the foundNewShip and 
    // foundDirect parameter.
    void initAI();
    
    // Function: placeShips - will randomly place the five distinct types ships
    // in a map for the AI reference and in an array for the controller class to
    // access. 
    void placeShips(ShipClass* shipArray[NUM_SHIPS]);
    
    // Function: checkValidCord - will check if the randomly coordinates for the
    // AI's next turn are within the map bounds and that a bomb has not been 
    // dropped in that location before. It will return true if the coordinates 
    // are valid, otherwise it return false.
    bool checkValidCord(int yCord, int xCord);
    
    // Function: checkShipPlacement - will ensure that when randomly placing 
    // ships they do not overlap each other or that they are placed outside 
    // bounds of the map. It will return true if the coordinates 
    // are valid, otherwise it return false.
    bool checkShipPlacement(int headYCord, int headXCord, bool isVertical, 
                            int shipIndex);
    
    // Function: makeMove - will make the next smart move to either continue the 
    // sinking process of a ship or try to find ships in the map.
    void makeMove(int &yCord, int &xCord, bool prevMoveWasHit);
    
    // Function: huntShip - will randomly shoot a bomb to an empty location in
    // the map. 
    void huntShip(int &yCord, int &xCord);
    
    // Function: findShipDirec - once a ship has been found this function will 
    // randomly guesses the direction of the ship (i.e. up, down, right, left). 
    // This function will be called in subsequent turns until the direction is 
    // found
    void findShipDirec(int &yCord, int&xCord);
    
    // Function: sinkShipOpp - in the case that the AI knows the direction of a 
    // ship and is dropping bombs in the the row or column, but reaches a 
    // map boundary, a bomb or an empty space then it will drop a bomb on the 
    // opposite side of the original location where the ship was found.
    void sinkShipOpp(int &yCord, int &xCord);
    
    // Function: sinkShip - with the direction of the ship known it will drop 
    // bombs in that direction from the location the ship was found
    void sinkShip(int &yCord, int &xCord);
    
    // Function: findNextMove - will decide what is the next smartest action to 
    // take given the results of the previous term. 
    void findNextMove(bool prevMoveWasHit, bool isShipSunk);
    
    // Function: foundNewShip - will set the private parameter of the AI that 
    // informs him that he has found a ship and is trying to sink it. It will  
    // also store the coordinates of the location where the ship was found.
    void foundNewShip();
    
    // Function: foundShipDirec - will se the private parameter of the AI that 
    // informs him that he has found the direction of the ship he is trying to 
    // sink.
    void foundShipDirec();
    
    // Function: printBombsMap - prints the map that stores where the AI has 
    // dropped bombs for his reference. 
    void printBombsMap();
    
    // Function: prinShipsMap - prints the map of the location of the AI's 
    // ships.
    void printShipsMap();
    
    // Functions: wasItAHit - function will receive a y and an x coordinate and 
    // will check if there is a ship in that location. If there is a ship in 
    // that location indicates that the enemy has hit one of ships and will 
    // return true.
    bool wasItAHit(int yCord, int xCord);
    


    
  	
   
};
#endif
 