/*
 * ControlClass.h
 *
 *  Created on: Apr 12, 2014
 *      Author: Mert Turkol
 * Description: Game engine controller interface for the turn based
 *              Networked BattleShip game.
 */

#ifndef CONTROLCLASS_H_
#define CONTROLCLASS_H_
#include <ncurses.h>
#include "GUIGLOBALCONSTANTS.h"
#include "MarkerClass.h"
#include "ShipClass.h"
#include "CursesGUI.h"
#include "ServerClass.h"
#include "ClientClass.h"
#include "AIClass.h"
#include <string>
using namespace std;

class ControlClass
{
  private:
    int totalShots; //to be updated each time the player fires to the enemy
    int numHitsScored; //to be updated each time a fired missile scores a hit on
                       //the enemy navy
    int enemyScore; //keeps track of how many hits the other player scored
                    //used for deciding end game criteria
  public:
    //def. ctor
    ControlClass()
    {
      totalShots = 0;
      numHitsScored = 0;
      enemyScore = 0;
    }

    //dtor
    ~ControlClass()
    {
      totalShots = 0;
      numHitsScored = 0;
      enemyScore = 0;
    }

    //Overloaded function, manages the entire defend against enemy fire process.
    //Uses the ServerClass object and its member functions if the player
    //calling this function is the server
    void defendAlly(MarkerClass** const &defenderGrid,
                    CursesGUI &defenderGUI,
                    ShipClass* defenderShipArray[NUM_SHIPS],
                    ServerClass &serverObj);

    //Overloaded function, manages the entire defend against enemy fire process.
    //Uses the ClientClass object and its member functions if the player
    //calling this function is the client
    void defendAlly(MarkerClass** const &defenderGrid,
                    CursesGUI &defenderGUI,
                    ShipClass* defenderShipArray[NUM_SHIPS],
                    ClientClass &clientObj);

    //Overloaded function that manages the entire attack on enemy process.
    //Uses the ServerClass object and its member functions if the player
    //calling this function is the server
    void attackEnemy(CursesGUI &attackerGUI,
                     ServerClass &serverObj);

    //Overloaded function that manages the entire attack on enemy process.
    //Uses the ClientClass object and its member functions if the player
    //calling this function is the client
    void attackEnemy(CursesGUI &attackerGUI,
                     ClientClass &clientObj);
    
    //Manages the entire attacking the computer process while
    //playing as single player against the PC artificial intelligence
    void attackAI(CursesGUI &myGUI,
                  MarkerClass** cpuGrid,
                  ShipClass* cpuShipsArry[NUM_SHIPS]);
    //Manages the entire defending against the computer process while
    //playing as single player against the PC artificial intelligence
    void attackHuman(AIClass &AI,
                     CursesGUI &myGUI,
                     MarkerClass** myAllyGrid,
                     ShipClass* myShipsArry[NUM_SHIPS]);
                     
    //Handles the outcome of an attack on an attacker's side based upon
    //the response that comes from the defender that used checkAllyHit func.
    void handleFireOutcome(const int inY, const int inX,
                           const bool isHit, const char sunkShipID,
                           CursesGUI &attackerGUI);

    //Overloaded function that in case of a networked game, takes the enemy's
    //shooting coordinates and checks if it corresponds to a hit on a user's
    //own ship map.
    bool checkAllyHit(const int inY, const int inX,
                      MarkerClass** const &allyGrid,
                      ShipClass* shipArray[NUM_SHIPS],
                      CursesGUI &allyGUI,
                      char &sunkShipID);

    //Overloaded function that in case of a single player game against the PC,
    //takes the human player's shooting coordinates and checks if it
    //corresponds to a hit on a the computer's own AI set-up artificial map.
    bool checkAllyHit(const int yCord, const int xCord,
                      MarkerClass** const &cpuGrid,
                      ShipClass* cpuShipsArray[NUM_SHIPS],
                      char &sunkShipID);

    //Maps the char representing a specific ship to a ship Name
    string convertCharToShipName(const char inShipID);

    //initializes the ally map's grid with 0 markers (just empty water)
    void initGrid(MarkerClass** &allyGrid);

    //After receiving information on placement of ships on the Ally Map
    //updates the marker grid with the exact locations of ships
    void getShipsAndSetGrid(ShipClass* const shipArray[NUM_SHIPS],
                            MarkerClass** &allyGrid);

    //Creates NUM_SHIPS number of ships to create a player's navy and assigns
    //them into a ship array
    void setShipArray(ShipClass* shipArray[NUM_SHIPS]);

    //Deletes the dynamically allocated player 2D map grid of markers
    void deleteAllyGrid(MarkerClass** &allyGrid);

    //Deletes the dynamically allocated ships
    void deleteShips(ShipClass* shipArray[NUM_SHIPS]);

    //Prints a greeting message with a ship image on the screen
    void greetPlayers();

    //return the number of hits made
    int getNumHits() const;

    //return the total number of shots fired
    int getTotalShots() const;

    //return the number of hits the enemy scored against the player
    int getEnemyScore() const;

    //converts a passed int to a string. Can be used for conversion to
    //GUI message data
    string convertIntToString(int inInt);

    //converts a passed float to a string. Can be used for conversion to
    //GUI message data
    string convertFloatToString(float inFloat);

    //converts a passed int to a char. Can be used for conversion to
    //socket suitable data
    char convertIntToChar(int inInt);

    //converts a passed char to an int. Can be used for conversion of
    //socket response data to be used for numerical evaluation
    int convertCharToInt(char inChar);

    //prints the end game statistics
    void printStats(CursesGUI &allyGUI);

    //Prints to the current order box and asks the player to press either
    // 'r' for replay or 'q' for quit.
    bool getReplayChoice(CursesGUI &allyGUI);
};

#endif /* CONTROLCLASS_H_ */
