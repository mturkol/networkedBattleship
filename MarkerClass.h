/******************************************************************************
 Date:              4/17/2014
 Author:            Alexander Vaughn and Mert Turkol
 File name:         MarkerClass.h
 Description:       Defines an object that will used to mark the games maps
                    with symbols that represent; open water, ship or bomb
 ******************************************************************************/
 
#ifndef MARKERCLASS_H_
#define MARKERCLASS_H_

#include "GUIGLOBALCONSTANTS.h"
#include "ShipClass.h"
#include <string>
using namespace std;

//Interface for markers making up a player's 2D grid that includes information
//about the ship name or water occupying the grid and whether an attack on 
//that point was a miss or hit
class MarkerClass
{
   private:
      int type; //type of marker:
                //0  - empty
                //-1 - miss
                //+1 - hit
                //+2 - undamaged ship piece
      string shipName; //has the name of the ship occupied by the marker
                       //equals "water" if the marker is not occupied by ship
   public:
      //initialize to blank marker (NULL pointer)
      MarkerClass();
      //rewrite marker to either hit or miss (1 or -1)
      void setMarkerHitStatus(bool isHit);
      //return the pointer to the ship that was hit
      string getMarkerShip() const;
      //rewrite marker to type of ship passed
      void setMarkerShip(const string inShipName);
      //get marker type at location
      int getMarkerType() const;
};

#endif // MARKERCLASS_H_
