/******************************************************************************
 Student Name:      Roberto Shu
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         AIClass.cpp
 Description:		class file that describes all parameters and functions for 
 					the games Artificial Intelligence. This class controls
 					everything related to the 1 player mode, where the user
 					plays against the computer. It will randomly place ships and 
 					intelligent drop bombs.
 ******************************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ShipClass.h"
#include "GUIGLOBALCONSTANTS.h"
#include "AIClass.h"

using namespace std;
 
void AIClass::initAI()
{
 
  newShipFound = false;
  foundDirec = false;
   
  // Initializes the Bombs and ships map to be all empty
  for(int i = 0; i < NUM_MAX_ROWS; i++)
  {
    for(int j = 0; j < NUM_MAX_COLS; j++)
    {
      bombsMap[i][j] = EMPTY;
      shipsMap[i][j] = EMPTY;
    }
  }
    
}
 
void AIClass::placeShips(ShipClass* shipArray[NUM_SHIPS])
{
  // sets the seed to randomly generate numbers depeding on the computer clock
  srand(time(0));
  bool isVertical; 
  int headXCord;
  int headYCord;
  int shipHP;  // number of ships hit points  
  bool validShipPlacement = false;
  
  for(int shipsPlaced = 0; shipsPlaced < NUM_SHIPS; shipsPlaced++)
  {
    // generate random head Y and X coordinate for ship and if it is vertical
    headYCord = rand()%NUM_MAX_ROWS;
    headXCord = rand()%NUM_MAX_COLS;
    isVertical = rand()%2;
    
    // get the hit points of the ship being placed
    shipHP = shipArray[shipsPlaced]->getHP();
    
    // check to see if placement of ship is valid
    validShipPlacement = checkShipPlacement(headYCord, headXCord, isVertical, 
                                            shipHP);
    
    // place ship if its valid or subtract one to the count of placed ships to 
    // account for the fail placement of ship
    if(validShipPlacement)
    {
 
      //Save ship position in array that is owned by the game controller
      shipArray[shipsPlaced]->setLoc(headYCord, headXCord, isVertical);
      
      if(isVertical)
      {
        for(int irow = headYCord; irow < headYCord+shipHP; irow++)
        {
          shipsMap[irow][headXCord] = shipsPlaced + 1;
        }
      }  
      else
      {
        for(int icol = headXCord; icol < headXCord+shipHP; icol++)
        {
          shipsMap[headYCord][icol] = shipsPlaced + 1;
        }
      }
    }
    else
    {
      shipsPlaced = shipsPlaced - 1;
    }
    
  }
}

bool AIClass::checkShipPlacement(int headYCord, int headXCord, bool isVertical,  
                                 int shipHP)
{
  bool validPlacement = false;
  bool overlap = false;
  bool outOfBounds = false;
  
  //Check if ships fits within the map bounds
  if(isVertical)
  {
    if(headYCord+shipHP >= NUM_MAX_ROWS)
    {
      outOfBounds = true;
    }
  }
  else
  {
    if(headXCord+shipHP >= NUM_MAX_COLS)
    {
      outOfBounds = true;
    }
  }
  
  //Check for overlap of ships
  if(isVertical)
  {
    for(int irow = headYCord; irow < headYCord+shipHP; irow++)
    {
      if(shipsMap[irow][headXCord] != EMPTY)
      {
        overlap = true;
      }
    }
  }
  else
  {
    for(int icol = headXCord; icol < headXCord+shipHP; icol++)
    {
      if(shipsMap[headYCord][icol] != EMPTY)
      {
        overlap = true;
      }
    }
  }
  
  if(!outOfBounds && !overlap)
  {
    validPlacement = true;
  }
  
  return validPlacement;
}

bool AIClass::checkValidCord(int yCord, int xCord)
{
  bool validCord;
  
  // First check if coordinate is within the bounds of the map
  if(yCord < NUM_MAX_ROWS && yCord >= NUM_MIN_ROWS
  && xCord >= NUM_MIN_COLS && xCord < NUM_MAX_COLS)
  {
    // Second check if the coordinate location is empty
    if(bombsMap[yCord][xCord] == EMPTY)
    {
      validCord = true;
    }
    else
    {
      validCord = false;
    }
  }
  else
  {
    validCord = false;
  }
  
  return validCord; 
}

void AIClass::makeMove(int &yCord, int &xCord, bool prevMoveWasHit)
{
   if(nextMove == FIND_DIREC)
   {
     findShipDirec(yCord, xCord);
   }
   else if(nextMove == SINK_SHIP)
   {
      sinkShip(yCord, xCord);
   }
   else if(nextMove == SINK_OPP)
   {
     sinkShipOpp(yCord, xCord);
   }
   else
   {
     huntShip(yCord, xCord);
   }
   
}

void AIClass::huntShip(int &yCord, int  &xCord)
{
 
  bool validCord = false;
  // while loop to check if BOMB has been dropped in random coordinates
  // if a BOMB has been previously dropped a new set of x and y coordinates
  // will be generated until an empty coordinate location is found 
  while(!validCord)
  {
     // Generates two random x and y coordinates
     srand(time(0));
     yCord = rand()%NUM_MAX_ROWS;
     xCord = rand()%NUM_MAX_COLS; 
     
     validCord = checkValidCord(yCord,xCord);
   }
   
   // updates the bombs map and data that the AI needs to decide on his next 
   // move
   bombsMap[yCord][xCord] = BOMB; 
   lastTurnYCord = yCord;
   lastTurnXCord = xCord; 
   lastMove = HUNT_SHIP;

}
 
 void AIClass::findShipDirec(int &yCord, int &xCord)
 {
   bool validCord = false;
   
   while(!validCord)
   {
     srand(time(0));
     
     // randomly generates an int between 0 and 3 that will correspond to a 
     // direction
     shipDirec = rand()%4;
     
     // set the y and x coordinate to where you initially found the ship to  
     // account for any miss hits when finding the direction
     yCord = foundShipAtYCord;
     xCord = foundShipAtXCord;
     
     if(shipDirec == UP)
     {
        yCord = yCord - 1;
        xCord = foundShipAtXCord;
     }
     else if(shipDirec == RIGHT)
     {
       yCord = foundShipAtYCord;
       xCord = xCord + 1;
     }
     else if(shipDirec == DOWN)
     {
       yCord = yCord + 1;
       xCord = foundShipAtXCord;
     }
     else if(shipDirec == LEFT)
     {
       yCord = foundShipAtYCord;
       xCord = xCord - 1;
     }
    
     //check for if coordinates are valid
     validCord = checkValidCord(yCord, xCord);
   }
   
   // updates the bombs map and data that the AI needs to decide on his next 
   // move
   bombsMap[yCord][xCord] = BOMB; 
   lastTurnYCord = yCord;
   lastTurnXCord = xCord; 
   lastMove = FIND_DIREC;
   
 }
 
 void AIClass::sinkShipOpp(int &yCord, int &xCord)
 {
   if(shipDirec == UP)
     {
       yCord = foundShipAtYCord + 1;
       xCord = foundShipAtXCord;
       
       // Set new direction for ship
       shipDirec = DOWN;
     }
     else if(shipDirec == RIGHT)
     {
       yCord = foundShipAtYCord;
       xCord = foundShipAtXCord - 1;
        
       // Set new direction for ship
       shipDirec = LEFT;
     }
     else if(shipDirec == DOWN)
     {
       yCord = foundShipAtYCord - 1;
       xCord = foundShipAtXCord;
       
       // Set new direction for ship
       shipDirec = UP;
     }
     else if(shipDirec == LEFT)
     {
       yCord = foundShipAtYCord;
       xCord = foundShipAtXCord + 1;
       
       // Set new direction for ship
       shipDirec = RIGHT;
     } 
   
   bool validCord;
   //check coordinates are valid
   validCord = checkValidCord(yCord, xCord);
   
   if(validCord)
   {
     // No need to worry about being out of bounds or that a BOMB is already in 
     // that location since we know that a BOMB has not been dropped there and 
     // the ship is still floating
     bombsMap[yCord][xCord] = BOMB; 
     lastTurnYCord = yCord;
     lastTurnXCord = xCord; 
     lastMove = SINK_OPP;
   }
   else
   {
     findShipDirec(yCord, xCord);
   }
 }
 
 void AIClass::sinkShip(int &yCord, int &xCord)
 {
   bool validCord;
   if(shipDirec == UP)
   {
     yCord = lastTurnYCord - 1;
     xCord = lastTurnXCord;
   }
   else if(shipDirec == RIGHT)
   {
     yCord = lastTurnYCord;
     xCord = lastTurnXCord + 1;
   }
   else if(shipDirec == DOWN)
   {
     yCord = lastTurnYCord + 1;
     xCord = lastTurnXCord;
   }
   else if(shipDirec == LEFT)
   {
     yCord = lastTurnYCord;
     xCord = lastTurnXCord - 1;
   }
   
   validCord = checkValidCord(yCord, xCord);
   
   // If coordinate are invalid it has to be because coordinates are out of 
   // bounds or there is already a BOMB in that location. Since the ship has not 
   // been sunk yet then the ship must extends in the opposite direction from 
   // the location the ship was found since the ship has not been sunk yet. 
   // Therefore, logically next BOMB will drop on the other side of the original 
   // ship found location
   if(!validCord)
   {
     sinkShipOpp(yCord,xCord);
   }
   
   bombsMap[yCord][xCord] = BOMB; 
   lastTurnYCord = yCord;
   lastTurnXCord = xCord; 
   lastMove = SINK_SHIP;
 }

 void AIClass::foundNewShip()
 {
   newShipFound = true;
   foundShipAtXCord = lastTurnXCord;
   foundShipAtYCord = lastTurnYCord;
 }
 
void AIClass::foundShipDirec()
{
  foundDirec = true;
}

bool AIClass::wasItAHit(int yCord, int xCord)
{
  bool hit;
  
  // if statements to determine what the next move needs to be considering the 
  // result of the last move
  if(shipsMap[yCord][xCord] != EMPTY)
  {
    hit = true;
    bombsMap[yCord][xCord] = HIT;
  }
  else
  {
    hit = false;
  }
  
  return hit;
}

void AIClass::findNextMove(bool prevMoveWasHit, bool isShipSunk)
{
  // if statements to determine what the next move needs to be considering the 
  // result of the last move
  if(prevMoveWasHit && !isShipSunk)
  {
    if(lastMove == HUNT_SHIP)
    {
      foundNewShip();
      nextMove = FIND_DIREC;
    }
    else if(lastMove == FIND_DIREC)
    {
      foundShipDirec();
      nextMove = SINK_SHIP;
    }
    else if(lastMove == SINK_SHIP)
    {
      nextMove = SINK_SHIP;
    }
    else if(lastMove == SINK_OPP)
    {
      nextMove = SINK_SHIP;
    }
  }
  else if(prevMoveWasHit && isShipSunk)
  {
    nextMove = HUNT_SHIP;
  }
  else if(!prevMoveWasHit && !isShipSunk) //if previous bomb drop was not a hit
  {
    if(lastMove == SINK_SHIP)
    {
      nextMove = SINK_OPP;
    }
    else if(lastMove == FIND_DIREC)
    {
      nextMove = FIND_DIREC;
    }  
  }
  else
  {
    nextMove = HUNT_SHIP;
  }
  
  if(isShipSunk)
  {
    newShipFound = false;
  }
  
  
}

void AIClass::printBombsMap()
{
  cout << endl << "Bombs Droped Location Map" << endl;
  for(int i = 0; i < NUM_MAX_ROWS; i++)
  {
    for(int j = 0; j < NUM_MAX_COLS; j++)
    {
      cout << bombsMap[i][j] << " " ;
    }
    cout << endl;
  }
}  

void AIClass::printShipsMap()
{
  cout << endl << "Ship Location Map" << endl;
  for(int i = 0; i < NUM_MAX_ROWS; i++)
  {
    for(int j = 0; j < NUM_MAX_COLS; j++)
    {
      cout << shipsMap[i][j] << " " ;
    }
    cout << endl;
  }
} 
