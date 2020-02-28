/******************************************************************************
 Date:              4/17/2014
 Author:            Alexander Vaughn and Mert Turkol
 File name:         ShipClass.h
 Description:       Interface for the ships that will represent the navy of 
                    a player or the computer
 ******************************************************************************/
#ifndef SHIPCLASS_H_
#define SHIPCLASS_H_

#include <string>

class ShipClass
{
   public:
       //initialize ship based on code passed
       //designating ship type (must be accurate)
      ShipClass(
                  const char code
               ); 
       //reduce hp by 1, if hp is zero, return true for ship
       //has been sunk
      bool addHit(
                 ); 
       //return name of battleship
      std::string getName(
                         ) const;
      //Maps the name of the ship to a char for easy use later on
      char getShipNameToChar();
       //return the number of hitpoints of the ship
      int getHP(
               ) const;
       //set all information constraining ship's location
      void setLoc(
                    int y,
                    int x,
                    bool vert
                 );
       //return ship headX
      int getHeadX(
                  ) const;
       //return ship headY
      int getHeadY(
                  ) const;
       //return ship orientation
      bool getIsVertical(
                        ) const;

   private:
       //number of ship hitpoints
      int hp; 
       //name of ship type
      std::string name;
      //X and Y coordinates of the ship head
      int headX,headY;
      //Orientation of the ship being whether vertical or horizontal
      bool isVertical;
};

#endif // SHIPCLASS_H_
