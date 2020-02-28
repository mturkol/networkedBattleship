/******************************************************************************
 Student Name:      Alexander Vaughn 
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WMap.h
 ******************************************************************************/
 
#ifndef WMAP_H
#define WMAPH_H
#include <ncurses.h>
#include "WindowClass.h"
#include "WBox.h"
#include "marker.inl"
#include "ShipClass.h"

class WMap: public WindowClass
{
   public:
       //initialize the 'map' type of window
      void init(
                  int height,
                  int width,
                  int starty,
                  int startx
               ); 

       //set all values in grid to zero
      void clearGrid(
                       marker grid[][10]
                    ); 
       //update map based on grid markers
      void wUpdate(
                  ); 
       //update grid coordinate to correct type
      void gridMark(
                      int y,
                      int x,
                      int type
                   );                     
       //interactively add to the grid, print info through boxes
       //can only overwrite water spaces
      void addPoint(
                      WBox& echoBox,
                      int &y,
                      int &x
                   );
       //interactively place a ship on the grid of the type
       //passed by the pointer. Manipulates ship based on hp
       //in ShipClass. Sets placement identifiers in ShipClass upon exit
      void placeShip(
                       WBox& echoBox,
                       ShipClass* ship
                    ); 
            
   private:
       //grid containing all map display data index is [y][x] (row then column)
      marker grid[10][10]; 
        //set the char at the passed coordinate to the
        //appropriate settings based on the passed type
      void wSetMark(
                      int y,
                      int x,
                      marker type
                   );
       //read from rGrid and write to wGrid (copy functionality)
       //this ONLY works for the grid types (marker[10][10])
      void copy(
                  marker rGrid[][10],
                  marker wGrid[][10]
               );
       //return false if moving to the new coordinate
       //would write ship off-screen
      bool checkBounds(
                         int cY,
                         int cX
                      );
       //place the shape on the map given the parameter
       //updates the member array 'grid'
       //does not update the screen
      void putShipCursor(
                           int hY,
                           int hX,
                           bool vert,
                           int size
                        );
       //the write grid will be overwritten with the values
       //from the read grid at the passed locus
       //does not update the screen
      void replaceCursor(
                           marker rGrid[][10],
                           marker wGrid[][10],
                           int hY,
                           int hX,
                           bool vert,
                           int size
                        );
       //check to see if the bounds are in the valid grid area
      bool checkBounds(
                         int hY,
                         int hX,
                         bool Vert,
                         int size
                      );
       //look at the read grid and check to see if the passed
       //ship locus overlaps with any other ships
      bool checkOverlap(
                          marker rGrid[][10],
                          int hY,
                          int hX,
                          bool vert,
                          int size
                       );
       //the foreground of the ship locus is changed to be the code
       //that was passed in
      void unhighlight(
                         int hY,
                         int hX,
                         bool vert,
                         int size,
                         char code
                      );                                          
};

#endif
