/*
 * ControlClass.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: Mert Turkol
 * Description: Implementation details of the game engine controller interface
 *              for the turn based Networked BattleShip game.
 */

#include <ncurses.h>
#include <iostream>
#include "GUIGLOBALCONSTANTS.h"
#include "ControlClass.h"
#include "ShipClass.h"
#include "CursesGUI.h"
#include "MarkerClass.h"
#include "ServerClass.h"
#include "ClientClass.h"
#include "AIClass.h"
#include <string>
#include <sstream>
using namespace std;

//Overloaded function, manages the entire defend against enemy fire process.
//Uses the ServerClass object and its member functions if the player
//calling this function is the server
void ControlClass::defendAlly(MarkerClass** const &defenderGrid,
                              CursesGUI &defenderGUI,
                              ShipClass* defenderShipArray[NUM_SHIPS],
                              ServerClass &serverObj)
{
  //define socket data that will be passed to listen to target X,Y locations
  //which the enemy fired at
  char incomingFireY, incomingFireX;
  //define the ship identifier to hold information of a ship if one is sunk
  char sunkShipID = NO_SHIP_ID;
  //listen to the coordinates the enemy is firing at
  serverObj.getResponse(incomingFireY, incomingFireX);
  //convert the socket data holding attacked location information into integers
  int targetY = convertCharToInt(incomingFireY);
  int targetX  = convertCharToInt(incomingFireX);
  //check if the enemy scored a hit. Update the sunkShipID if he sunk a ship
  //return the outcome of the attack as true if successful, otherwise false
  bool isHit = checkAllyHit(targetY, targetX,
                            defenderGrid,
                            defenderShipArray,
                            defenderGUI,
                            sunkShipID);
  //convert the boolean isHit into a char so that it can be sent as a response
  //to the enemy attack process
  char hitStatus;//holds the outcome of the enemy attack to be sent as response
  if (!isHit)
  {
    hitStatus = '0';//the attack missed the defender's ships
  }
  else
  {
    hitStatus = '1';//the attack was successful as a hit on the defender navy
  }
  //report back whether the enemy attack was successful or not, along with
  //the identifier of the ship that was sunk if it sunk any ship
  serverObj.sendResponse(hitStatus, sunkShipID);
}

//Overloaded function, manages the entire defend against enemy fire process.
//Uses the ClientClass object and its member functions if the player
//calling this function is the client
void ControlClass::defendAlly(MarkerClass** const &defenderGrid,
                              CursesGUI &defenderGUI,
                              ShipClass* defenderShipArray[NUM_SHIPS],
                              ClientClass &clientObj)
{
  //define socket data that will be passed to listen to target X,Y locations
  //which the enemy fired at
  char incomingFireY, incomingFireX;
  //define the ship identifier to hold information of a ship if one is sunk
  char sunkShipID = NO_SHIP_ID;
  //listen to the coordinates the enemy is firing at
  clientObj.getResponse(incomingFireY, incomingFireX);
  //convert the socket data holding attacked location information into integers
  int targetY = convertCharToInt(incomingFireY);
  int targetX  = convertCharToInt(incomingFireX);
  //check if the enemy scored a hit. Update the sunkShipID if he sunk a ship
  //return the outcome of the attack as true if successful, otherwise false
  bool isHit = checkAllyHit(targetY, targetX,
                            defenderGrid,
                            defenderShipArray,
                            defenderGUI,
                            sunkShipID);
  //convert the boolean isHit into a char so that it can be sent as a response
  //to the enemy attack process
  char hitStatus;//holds the outcome of the enemy attack to be sent as response
  if (!isHit)
  {
    hitStatus = '0';//the attack missed the defender's ships
  }
  else
  {
    hitStatus = '1';//the attack was successful as a hit on the defender navy
  }
  //report back whether the enemy attack was successful or not, along with
  //the identifier of the ship that was sunk if it sunk any ship
  clientObj.sendResponse(hitStatus, sunkShipID);
}

//Overloaded function that manages the entire attack on enemy process.
//Uses the ServerClass object and its member functions if the player
//calling this function is the server
void ControlClass::attackEnemy(CursesGUI &attackerGUI,
                               ServerClass &serverObj)
{
  int targetY, targetX; //for choosing the location to attack on enemy map
  char isHit; //holds the value of a socket response in case of a sunk ship
  //isHit is 0 for a shot that the attacker misses, and 1 for a hit he scores
  char sunkShipID = NO_SHIP_ID; //identifies a sunk ship
  //choose a location on enemy map in GUI to fire at
  attackerGUI.getTarget(targetY, targetX);
  //convert integer targetX,Y into chars to be used by the socket interface
  char socketInY = convertIntToChar(targetY);
  char socketInX = convertIntToChar(targetX);

  //send the target X,Y coordinates to the other player to attack him
  serverObj.sendResponse(socketInY, socketInX);
  //start listening to the response of the enemy for the outcome of attack
  //enemy should send a response with his own ControllClass::checkAllyHit()
  serverObj.getResponse(isHit, sunkShipID);
  //missile is sent, update the total number of shots fired at the enemy
  totalShots++;
  //convert the socket response isHit which is a char into a boolean
  bool hitStatus;
  if(isHit == '0') //when the attacker misses his target
  {
    hitStatus = false; //update the hitStatus to a miss
  }
  else //when the attacker scores a hit on the enemy
  {
    hitStatus = true; //update the hitStatus to a hit
    numHitsScored++;
  }
  //update statistics and inform the attacker of the outcome
  handleFireOutcome(targetY, targetX,
                    hitStatus, sunkShipID,
                    attackerGUI);
}

//Overloaded function that manages the entire attack on enemy process.
//Uses the ClientClass object and its member functions if the player
//calling this function is the client
void ControlClass::attackEnemy(CursesGUI &attackerGUI,
                               ClientClass &clientObj)
{
  //define input and output string streams to be used for intTochar conversions
  int targetY, targetX; //for choosing the location to attack on enemy map
  char isHit; //holds the value of a socket response in case of a sunk ship
  //isHit is 0 for a shot that the attacker misses, and 1 for a hit he scores
  char sunkShipID = NO_SHIP_ID; //identifies a sunk ship
  //choose a location on enemy map in GUI to fire at
  attackerGUI.getTarget(targetY, targetX);
  //convert integer targetX,Y into chars to be used by the socket interface
  char socketInY = convertIntToChar(targetY);
  char socketInX = convertIntToChar(targetX);

  //send the target X,Y coordinates to the other player to attack him
  clientObj.sendResponse(socketInY, socketInX);
  //start listening to the response of the enemy for the outcome of attack
  //enemy should send a response with his own ControllClass::checkAllyHit()
  clientObj.getResponse(isHit, sunkShipID);
  //missile is sent, update the total number of shots fired at the enemy
  totalShots++;
  //convert the socket response isHit which is a char into a boolean
  bool hitStatus;
  if(isHit == '0') //when the attacker misses his target
  {
    hitStatus = false; //update the hitStatus to a miss
  }
  else //when the attacker scores a hit on the enemy
  {
    hitStatus = true; //update the hitStatus to a hit
    numHitsScored++;
  }
  //update statistics and inform the attacker of the outcome
  handleFireOutcome(targetY, targetX,
                    hitStatus, sunkShipID,
                    attackerGUI);
}

//Handles the outcome of an attack on an attacker's side based upon
//the response that comes from the defender that used checkAllyHit func.
void ControlClass::handleFireOutcome(const int inY, const int inX,
                                     const bool isHit,
                                     const char sunkShipID,
                                     CursesGUI &attackerGUI)
{
  string dispAllyMsg = ""; //blank for now, later will be updated with hit/miss
  ostringstream convertIntToString; //to hold information about the int to be
  //converted into a string through the use of string stream
  convertIntToString.clear();//clear the string stream
  convertIntToString.str("");//set the string stream to blank
  //to report the  Y and X coordinate the attacker fired at
  convertIntToString << "(" << inY << ", " << inX << "). ";
  string convertedYX = convertIntToString.str(); //convert int to a string
  //set up the initial message to the attacker player about where he fired at
  string msgAllyFire = "You have fired at location " + convertedYX;

  if (isHit) //if the attacker scored a hit on the enemy navy
  {
    ////Update the enemy Map
    attackerGUI.enemyMMark(inY, inX, HIT_MARKER);
    //prepare the information message to be passed to the ally screen
    dispAllyMsg = msgAllyFire + "You scored a hit on an enemy ship!";
    //attacker player's screen should print this to his communication box
    attackerGUI.pLComm(dispAllyMsg);

    if(sunkShipID != NO_SHIP_ID)
    {
      //Find the ship that was sunk
      string sunkShipName = convertCharToShipName(sunkShipID);
      //Update the enemy List on the attacker screen
      attackerGUI.enemyLMark(sunkShipID);
      //Prepare the message to be displayed on the attacker screen
      dispAllyMsg = msgAllyFire + "You sunk the enemy " + sunkShipName + "!";
      //attacker's screen should inform the player by printing the message
      attackerGUI.pLComm(dispAllyMsg);
    }//end of if-sunk case
  }//end of if-hit case
  else //if the attacker missed with his shot
  {
    //Update the attacker's enemy Map
    attackerGUI.enemyMMark(inY, inX, MISS_MARKER);
    //prepare the message to be communicated to the ally regarding enemy miss
    dispAllyMsg = msgAllyFire + "Your shot missed the enemy ships! ";
    //Inform the player who fired his shot that he missed with a proper
    attackerGUI.pLComm(dispAllyMsg);
  }//end of if-miss case
}

//Manages the entire attacking the computer process while
//playing as single player against the PC artificial intelligence
void ControlClass::attackAI(CursesGUI &myGUI,
                            MarkerClass** cpuGrid,
                            ShipClass* cpuShipsArry[NUM_SHIPS])
{
  int yCord,xCord; //to be used for target coordinates to attack the computer
  char sunkShipID; //to be assigned to a sunk computer ship if the hit does so
  bool prevMoveWasHit = false; //indicates whether attack on computer was
                               //a hit or miss
  
  myGUI .getTarget(yCord,xCord); //select the target location on GUI map
  totalShots++; //the #shots in incremented
  sunkShipID = NO_SHIP_ID; //initialized to a no ship state
  //fires at the computer and returns the result as a hit or miss using bool
  prevMoveWasHit = checkAllyHit(yCord, xCord, cpuGrid, cpuShipsArry, 
                                sunkShipID);
  //according to the outcome of the attack against the computer,
  //handles the proper informative messages and statistical updates
  handleFireOutcome(yCord, xCord, prevMoveWasHit, sunkShipID, myGUI);
}

//Manages the entire defending against the computer process while
//playing as single player against the PC artificial intelligence
void ControlClass::attackHuman(AIClass &AI,
                               CursesGUI &myGUI,
                               MarkerClass** myAllyGrid,
                               ShipClass* myShipsArry[NUM_SHIPS])
{
  int yCord,xCord; //to be assigned for the computer's attacking coordinates
                   //against the human player
  char sunkShipID; //to hold ID information about a human ship if sunk
  bool prevMoveWasHit = false; //to hold info about computer's attack success
  bool isAllyShipSunk = false; //indicates whether a human ship was sunk or not
  
  //the computer attacks on a target human map location
  AI.makeMove(yCord,xCord, prevMoveWasHit);
  //the outcome of the computer's attack is returned as a hit or miss
  prevMoveWasHit = checkAllyHit(yCord, xCord, myAllyGrid, myShipsArry, myGUI, 
                                sunkShipID);
  if(sunkShipID != NO_SHIP_ID) //when computer's attack sinks a human ship
  {
    isAllyShipSunk = true; //sunk human ship state is true
  }
  else //when computer's attack cannot sink a human ship
  {
    isAllyShipSunk = false; //sunk human ship state is false
  }
  // Using the information from the previous turn the AI will determine 
  // his next move
  AI.findNextMove(prevMoveWasHit, isAllyShipSunk);                              
}

//Overloaded function that in case of a networked game, takes the enemy's
//shooting coordinates and checks if it corresponds to a hit on a user's
//own ship map.
bool ControlClass::checkAllyHit(const int inY, const int inX,
                                MarkerClass** const &allyGrid,
                                ShipClass* shipArray[NUM_SHIPS],
                                CursesGUI &allyGUI,
                                char &sunkShipID)
{
  bool gotHit = false; //indicates whether ally ship was hit or not
  bool gotSunk = false; //indicates whether ally ship was sunk or not
  //set up the display and information messages to be shown to the user
  string dispAllyMsg = ""; //blank for now, later will be updated with hit/miss
  ostringstream convertIntToString; //to hold information about the int to be
  //converted into a string through the use of string stream
  convertIntToString.clear();//clear the string stream
  convertIntToString.str("");//set the string stream to blank
  //to report the enemy fire Y and X coordinate
  convertIntToString << "(" << inY << ", " << inX << "). ";
  string convertedYX = convertIntToString.str(); //convert int to a string
  //set up the initial message to the defending player about where his enemy
  //has fired at
  string msgEnemyFire = "Your enemy has fired at location " + convertedYX;

  //learn whether a hit was taken and handle accordingly
  if (allyGrid[inY][inX].getMarkerType() == SHIP_MARKER) //hit case
  {
    gotHit = true; //enemy scored a hit
    enemyScore++; //increment the enemy score counter

    //learn name of the ship that got hit
    string hitShipName = allyGrid[inY][inX].getMarkerShip();

    //prepare the information message to be passed to the ally screen
    dispAllyMsg = msgEnemyFire + "The enemy has hit your " + hitShipName + "!";

    //Inform the ally that he got hit
    allyGUI.pLComm(dispAllyMsg);

    int hitShipIndex = 0; //to loop among the shipArray items
    bool hitShipFound = false; //to find which ship in array got hit

    while (!hitShipFound) //loop among shipArray items to find the damaged ship
    {
      hitShipFound = (hitShipName == shipArray[hitShipIndex]->getName());
      if(!hitShipFound)
      {
        hitShipIndex++;
      }
    }
    //Decrease HP of the ship that got hit, and get boolean on its sunk status
    //gotSunk represents sunk status
    gotSunk = shipArray[hitShipIndex]->addHit();

    //Update the ally map
    allyGUI.allyMMark(inY, inX);

    if (gotSunk) //in the case the enemy sunk one of the ships
    {
      //map the hit ship to a char so that the informative func. operating
      //on the Ship List in GUI can use that.
      sunkShipID = shipArray[hitShipIndex]->getShipNameToChar();
      //update the ally ship List on the screen with the sunk ship crossed out
      allyGUI.allyLMark(sunkShipID);
      //prepare the message to be communicated to the ally
      dispAllyMsg = msgEnemyFire + "The enemy has sunk your " +
                   hitShipName + "!";
      //inform the ally by printing to his communication box
      allyGUI.pLComm(dispAllyMsg);
    }//end of if-gotSunk
  }//end of if-hit
  else //if the enemy missed his fire on your navy
  {
    //prepare the message to be communicated to the ally regarding enemy miss
    dispAllyMsg = msgEnemyFire + "The enemy missed his shot! ";
    //inform the ally that the enemy has missed his shot
    allyGUI.pLComm(dispAllyMsg);
  }
  return gotHit;
}//end of func.

//Overloaded function that in case of a single player game against the PC,
//takes the human player's shooting coordinates and checks if it
//corresponds to a hit on a the computer's own AI set-up artificial map.
bool ControlClass::checkAllyHit(const int yCord, const int xCord,
                                MarkerClass** const &cpuGrid,
                                ShipClass* cpuShipsArray[NUM_SHIPS],
                                char &sunkShipID)
{
  bool gotHit = false; //indicates whether ally ship was hit or not
  bool gotSunk = false; //indicates whether ally ship was sunk or not

  //learn whether a hit was taken and handle accordingly
  if (cpuGrid[yCord][xCord].getMarkerType() == SHIP_MARKER) //hit case
  {
    gotHit = true; //enemy scored a hit
    numHitsScored++; //increment the enemy score counter

    //learn name of the ship that got hit
    string hitShipName = cpuGrid[yCord][xCord].getMarkerShip();

    int hitShipIndex = 0; //to loop among the shipArray items
    bool hitShipFound = false; //to find which ship in array got hit

    while (!hitShipFound) //loop among shipArray items to find the damaged ship
    {
      hitShipFound = (hitShipName == cpuShipsArray[hitShipIndex]->getName());
      if(!hitShipFound)
      {
        hitShipIndex++;
      }
    }
    //Decrease HP of the ship that got hit, and get boolean on its sunk status
    //gotSunk represents sunk status
    gotSunk = cpuShipsArray[hitShipIndex]->addHit();


    if (gotSunk) //in the case the enemy sunk one of the ships
    {
      //map the hit ship to a char so that the informative func. operating
      //on the Ship List in GUI can use that.
      sunkShipID = cpuShipsArray[hitShipIndex]->getShipNameToChar();

    }//end of if-gotSunk
  }//end of if-hit
  
  return gotHit;
}//end of func.

//Maps a certain ship ID to a ship name and returns that name of the ship
string ControlClass::convertCharToShipName(const char inShipID)
{
  string mappingShipName;

  if( inShipID == AIRCRAFT_CARRIER_ID)
  {
    mappingShipName = "Aircraft Carrier";
  }
  else if( inShipID == BATTLESHIP_ID)
  {
    mappingShipName = "Battleship";
  }
  else if( inShipID == SUBMARINE_ID)
  {
    mappingShipName = "Submarine";
  }
  else if( inShipID == DESTROYER_ID)
  {
    mappingShipName = "Destroyer";
  }
  else if( inShipID == PATROL_SHIP_ID)
  {
    mappingShipName = "Patrol Ship";
  }

  return mappingShipName; //report back the name of the ship identified
}

//initializes the ally map's grid with 0 markers (just empty water)
void ControlClass::initGrid(MarkerClass** &allyGrid)
{
  allyGrid = new MarkerClass*[NUM_MAX_ROWS]; //pointers to an array of
  //pointers which themselves will point to objects of MarkerClass

  //loop over the pointers as rows of an map matrix
  for (int iAllocRow = 0; iAllocRow < NUM_MAX_ROWS; iAllocRow++)
  {
    //pointers pointing to MarkerClass objects that hold  info about
    //coordinates of a map location
    allyGrid[iAllocRow] = new MarkerClass[NUM_MAX_COLS];
  }
}

//After receiving information on placement of ships on the Ally Map
//updates the marker grid with the exact locations of ships
void ControlClass::getShipsAndSetGrid(ShipClass* const shipArray[NUM_SHIPS],
                                      MarkerClass** &allyGrid)
{
  int xCoord; //to be assigned to x coordinates of the head of a ship
  int yCoord; //to be assigned to y coordinates of the head of a ship
  bool isVertical; //to be assigned to the orientation status of a ship
  int shipLength; //to be assigned to the length of a ship

  //loop over the ships in the array that holds the navy information
  for (int iShip = 0; iShip < NUM_SHIPS; iShip++)
  {
    xCoord = shipArray[iShip]->getHeadX(); //learn ship head's X-coordinate
    yCoord = shipArray[iShip]->getHeadY(); //learn ships head's Y-coordinate
    isVertical = shipArray[iShip]->getIsVertical(); //learn ship's orientation
    shipLength = shipArray[iShip]->getHP(); //learn ship's length in markers

    //place the ship on the marker grid based upon its X-Y coordinates and
    //its orientation
    if (isVertical) //update the markers in Y-direction using rows of the grid
    {
      for (int iRow = yCoord; iRow <= (yCoord+shipLength-1); iRow++)
      {
        allyGrid[iRow][xCoord].setMarkerShip(shipArray[iShip]->getName());
      }
    } //end of placing ships if in vertical orientation
    else //update the markers in X-direction using columns of the grid
    {
      for (int jColumn = xCoord; jColumn <= (xCoord+shipLength-1); jColumn++)
      {
        allyGrid[yCoord][jColumn].setMarkerShip(shipArray[iShip]->getName());
      }
    }//end of updating the markers related to a specific ship object
  }//end of the loop spanning the shipArray
}//end of function

//Creates NUM_SHIPS number of ships to create a player's navy and assigns
//them into the ship array passed by reference
void ControlClass::setShipArray(ShipClass* shipArray[NUM_SHIPS])
{
  ShipClass* airCarrier = new ShipClass(AIRCRAFT_CARRIER_ID);
  shipArray[0] = airCarrier;
  ShipClass* battleShip = new ShipClass(BATTLESHIP_ID);
  shipArray[1] = battleShip;
  ShipClass* submarine = new ShipClass(SUBMARINE_ID);
  shipArray[2] = submarine;
  ShipClass* destroyer = new ShipClass(DESTROYER_ID);
  shipArray[3] = destroyer;
  ShipClass* patrolShip = new ShipClass(PATROL_SHIP_ID);
  shipArray[4] = patrolShip;
}

//Deletes the marker pointers pointing to 2D the marker grid 
void ControlClass::deleteAllyGrid(MarkerClass** &allyGrid)
{
  for (int iMarker = 0; iMarker < (NUM_MAX_ROWS); iMarker++)
  {
    delete [] allyGrid[iMarker]; //intended for the innermost 1D column array
    //of pointers that point to objects of MarkerClass
  }
  delete [] allyGrid; //intended for the outer 1D row array of pointers
                      //pointing to columns of the 2D map grid of Markers
}

//Deletes ship pointers pointing to dynamically allocated ships
void ControlClass::deleteShips(ShipClass* shipArray[NUM_SHIPS])
{
  for (int iShip = 0; iShip < NUM_SHIPS; iShip++)
  {
    delete shipArray[iShip]; //intended for the innermost 1D arrays
    //of pointers that point to objects of ColorClass
  }
}

//Converts a passed int to a string. Can be used for conversion to
//GUI message data
string ControlClass::convertIntToString(int inInt)
{
  //define input and output string streams to be used for intTochar conversions
  stringstream converterToString;

  string outString; //data to be returned as a socket-friendly version

  converterToString.clear();
  converterToString.str("");
  converterToString << inInt;
  outString = converterToString.str();

  return outString; //return the int data converted into char which is now
                       //usable by a socket
}

//converts a passed float to a string. Can be used for conversion to
//GUI message data
string ControlClass::convertFloatToString(float inFloat)
{
  //define input and output string streams to be used for intTochar conversions
  stringstream converterToString;

  string outString; //data to be returned as a string

  converterToString.clear();
  converterToString.str("");
  converterToString << inFloat;
  outString = converterToString.str();

  return outString; //return the float data converted into string which is now
}

//converts a passed int to a char. Can be used for conversion to
//socket suitable data
char ControlClass::convertIntToChar(int inInt)
{
  //define input and output string streams to be used for intTochar conversions
  stringstream ss;

  char socketInData; //data to be returned as a socket-friendly version

  ss.clear();
  ss.str("");
  ss << inInt;
  ss >> socketInData;

  return socketInData; //return the int data converted into char which is now
                       //usable by a socket
}

//converts a passed char to an int. Can be used for conversion of
//socket response data to be used for numerical evaluation
int ControlClass::convertCharToInt(char inChar)
{
  int numericInData; //data to be returned as an int to be used for
                     //numeric evaluations

  //define input and output string streams to be used for charToInt conversions
  stringstream ss;
  ss.clear();
  ss.str("");
  ss << inChar;
  ss >> numericInData;

  return numericInData; //return the char data converted into an int which is
                        //now usable for numeric evaluations.
}

void ControlClass::greetPlayers()
{
  cout << endl << endl <<"                                      |__" << endl;
  cout << "                                      |\\/" << endl;
  cout << "                                      ---" << endl;
  cout << "                                     / | [" << endl;
  cout << "                              !      | |||" << endl;
  cout << "                            _/|     _/|-++'" << endl;
  cout << "                        +  +--|    |--|--|_ |-" << endl;
  cout << "                     { /|__|  |/\\__|  |--- |||__/" << endl;
  cout << "                    +---------------___[}-_===_.'____                 /\\" << endl;
  cout << "                ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _" << endl;
  cout << " __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7" << endl;
  cout << "|              BattleShip                                                   BB-61/" << endl;
  cout << " \\_________________________________________________________________________|" << endl;
  cout << "Image by Matthew Bace" << endl<< endl;
  cout << "~~~~game by Mert Turkol, Roberto Shu, Alexander Vaughn~~~~~" << endl<< endl;
  cout << "Welcome to the Networked Battleship Game!" << endl;
}

//return the number of hits made
int ControlClass::getNumHits() const
{
   return(numHitsScored);
}

//return the total number of shots fired
int ControlClass::getTotalShots() const
{
  return totalShots;
}

//return the number of hits the enemy scored against the player
int ControlClass::getEnemyScore() const
{
  return enemyScore;
}

//prints the end game statistics
void ControlClass::printStats(CursesGUI &allyGUI)
{
  //finds who won the game
  bool isPlayerWinner = (getNumHits() == SCORE_LIMIT);
  //Prepare message depending on whether the player won or lost
  string winLoseMsg = "You won! ";

  if (!isPlayerWinner) //if the player lost
  {
    winLoseMsg = "You lost! ";
  }
  float successRate = (static_cast<float>(numHitsScored)) / totalShots * 100;
  //prepare the statistics to be printed
  string statsMsg = " Your Total #shots: "
  + convertIntToString(totalShots)
  + ", #hits scored: "
  + convertIntToString(numHitsScored)
  + ",success: "
  + convertFloatToString(successRate)
  + "%%";

  //prepare the final msg to displayed
  string gameSummary = winLoseMsg + statsMsg;
  allyGUI.pLComm(gameSummary);//broadcast to last communication box in GUI
}

//Prints to the current order box and asks the player to press either
// 'r' for replay or 'q' for quit.
bool ControlClass::getReplayChoice(CursesGUI &allyGUI)
{
  //prepare the end game message asking if the player wants a replay
  string lastOrderMsg = "Press 'r' if you want to replay, or 'q' to quit.";
  //broadcast the message into the current orders box in GUI
  allyGUI.pCOrd(lastOrderMsg);

  char inKey; //holds the entered key input
  bool isReplay = false; //holds info about whether player wants a replay
  bool validKey = false; //holds whether a valid key is pressed; r or q

  while( !validKey )
  {
    if( ( inKey = getch() ) == 'r' )
    {
      validKey = true;
      isReplay = true;
      //reinitialize counters to everything
      totalShots = 0;
      numHitsScored = 0;
      enemyScore = 0;
    }
    else if (( inKey = getch() ) == 'q' )
    {
      validKey = true;
    }
  }

  return isReplay; //return the choice about a replay
}

