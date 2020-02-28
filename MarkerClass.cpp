/******************************************************************************
 Date:              4/17/2014
 Author:            Alexander Vaughn and Mert Turkol
 File name:         MarkerClass.h
 Description:       Defines member functions of an object that will be used to
                    mark the games maps with symbols that represent; open water,
                    ship or bomb
 ******************************************************************************/
 
#include "MarkerClass.h"
#include "GUIGLOBALCONSTANTS.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

MarkerClass::MarkerClass()
{
   type = EMPTY_MARKER; //initialize to empty
   shipName= "water"; //no ships residing at the point pointed by the marker
}

//Sets a specific marker's pointer to the ship so that a given ship consumes
//that marker's location
void MarkerClass::setMarkerShip(const string inShipName)
{
   type = SHIP_MARKER; //ship placed on tile
   shipName = inShipName; //set ship to point to passed ship class object
}

//Sets a specific marker's type to either hit or miss depending on the passed
//hit status boolean
void MarkerClass::setMarkerHitStatus(bool isHit)
{
   if(isHit)
   {
      type = HIT_MARKER; //indicates a hit
   }
   else
   {
      type = MISS_MARKER; //indicates a miss
   }
   return;
}

//gets and returns the name of the ship if there is one occupying the marker
string MarkerClass::getMarkerShip() const
{
   return(shipName);
}

//gets and returns what type of marker 
int MarkerClass::getMarkerType() const
{
   return(type);
}
