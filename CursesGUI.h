/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         CursesGUI.h
 Description:		Class that manages all the GUI of the game
 ******************************************************************************/
 
#ifndef CURSESGUI_H
#define CURSESGUI_H
#include <ncurses.h>
#include <string>
#include "WMap.h"
#include "WBox.h"
#include "WList.h"
#include "string.h"
#include "GUIGLOBALCONSTANTS.h"
#include "ShipClass.h"

class CursesGUI
{
   public:
       //initializer with correct call
      CursesGUI(
               ); 
       //deconstructor
      ~CursesGUI(
                ); 
       //print to LAST COMM line; clears old line
      void pLComm(
                   std::string str
                 ); 
       //print to CURR ORDER line; clears old line
      void pCOrd(
                   std::string str
                ); 
       //pass ship type sunk and mark
      void allyLMark(
                       char type
                    ); 
      void enemyLMark(
                       char type
                    );
       //at passed grid coord, update to a hit was made
       //we only keep track of the enemy's hits on our map,
       //so this will only be called in case of a hit
      void allyMMark(
                       int y,
                       int x
                     );

      void enemyMMark(
                        int y,
                        int x,
                        int type
                     );
       //via GUI, get user to input coordinate to attack
       //writes to reference passed x and y coordinate
      void getTarget(
                       int &y,
                       int &x
                    ); 
                    
       //get user to place ships on the grid updates the ship
       //updates ship placement inormation via the array of
       //pointers to ShipClass objects
      void placeShips(
                        ShipClass* shipArray[NUM_SHIPS]
                     );
      void Break(); //debugging function 
                      

   private:
       //class handling window for friendly ship grid  
      WMap allyMap;            
       //class handling window for foe ship grid
      WMap enemyMap; 
       //window for information returns from program
      WBox echoBox; 
       //window for ally target status
      WList allyList; 
       //window for enemy target status
      WList enemyList; 
};
#endif
