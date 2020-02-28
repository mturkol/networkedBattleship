/******************************************************************************
 Date:              4/17/2014
 Author:            Alexander Vaughn and Mert Turkol
 File name:         ShipClass.cpp
 Description:       Defines the member function implementations of the ship
                    interface that will represent the navy of 
                    a player or the computer
 ******************************************************************************/
 
#include "ShipClass.h"
#include "GUIGLOBALCONSTANTS.h"

ShipClass::ShipClass(
                       const char init
                    )
{
   if( init == AIRCRAFT_CARRIER_ID )
      {
         hp= LENGTH_AIRCRAFT;
         name="Aircraft Carrier";
      }
   else if ( init == BATTLESHIP_ID )
      {
         hp=LENGTH_BATTLESHIP;
         name="Battleship";
      }
   else if ( init == SUBMARINE_ID )
      {
         hp=LENGTH_SUBMARINE;
         name="Submarine";
      }
   else if ( init == DESTROYER_ID )
      {
         hp=LENGTH_DESTROYER;
         name="Destroyer";
      }
   else if ( init == PATROL_SHIP_ID )
      {
         hp=LENGTH_PATROLSHIP;
         name="Patrol Ship";
      }
}

//True and puts a hit on a specific ship, lowering its Health Points (hp)
bool ShipClass::addHit(
                      )
{
   hp--;
   if ( hp == 0 )
   {
       //ship has been sunk
      return(true); 
   }
    //ship has not been sunk yet
   return(false); 
}

//Gets the name of a specific ship
std::string ShipClass::getName(
                              ) const
{
   return(name);
}

//maps the ship name to an identifier char for easy use later on
char ShipClass::getShipNameToChar()
{
  char mappingChar;

  if( name == "Aircraft Carrier")
  {
    mappingChar = AIRCRAFT_CARRIER_ID;
  }
  else if( name == "Battleship")
  {
    mappingChar = BATTLESHIP_ID;
  }
  else if( name == "Submarine")
  {
    mappingChar = SUBMARINE_ID;
  }
  else if( name == "Destroyer")
  {
    mappingChar = DESTROYER_ID;
  }
  else if( name == "Patrol Ship")
  {
    mappingChar = PATROL_SHIP_ID;
  }

  return mappingChar; // returns the char mapping to a ship
}

//Gets and return the remaning HP of a ship
int ShipClass::getHP(
                    ) const
{
   return(hp);
}

//Sets the location of a ship
void ShipClass::setLoc(
                         int y,
                         int x,
                         bool vert
                      )
{
   headY=y;
   headX=x;
   isVertical=vert;
   return;
}

//Gets and returns a ship head's X-location
int ShipClass::getHeadX(
                       ) const
{
   return(headX);
}

//Gets and returns a ship head's Y-location
int ShipClass::getHeadY(
                       ) const
{
   return(headY);
}

//Boolean that defines a ship's horizontal or verical orientation on the map
bool ShipClass::getIsVertical(
                             ) const
{
   return(isVertical);
}
