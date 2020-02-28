/******************************************************************************
 Student Name:      Alexander Vaughn 
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WMap.cpp
 Description:       Implementation of the ship 2d grid visual display	
 ******************************************************************************/
 
#include "WMap.h"
#include "GUIGLOBALCONSTANTS.h"
#include <string>

void WMap::init(
                  int height,
                  int width,
                  int starty,
                  int startx
               )
{
   map = newwin(height, width, starty, startx);
    //0, 0 gives default characters for the vertical and horizontal line
   box(map,0,0); 
   xEnd=width-1;
   yEnd=height-1;
    //initialize grid as empty
   clearGrid(grid); 
   for( int r = 1 ; r < yEnd ; r++ )
   {
      for( int c = 1 ; c < xEnd ; c++ )
      {
         mvwaddch(map,r,c,'0');
      }
   }
   refresh();
   wUpdate();
}

void WMap::clearGrid(
                       marker grid[][NUM_MAX_COLS]
                    )
{
   for( int r = 0 ; r < NUM_MAX_ROWS ; r++ )
   {
      for( int c = 0 ; c < NUM_MAX_COLS ; c++ )
      {
         grid[r][c].bg=0;
         grid[r][c].fg=' ';
      }
   }
}

void WMap::wUpdate(
                  )
{
   int x,y;
   char block;
   for( int r = 0 ; r < NUM_MAX_ROWS ; r++ )
   {
       //loop through grid array
      for( int c = 0 ; c < NUM_MAX_COLS ; c++ ) 
      {
         wSetMark(r,c,grid[r][c]);  
      }
   } 
   refresh();
}

void WMap::wSetMark(
                      int y,
                      int x,
                      marker type
                   )
{
   y=y*MMH+1;
   x=x*MMW+1;
   int color;
   if( type.fg == '#' )
   {
      if( type.bg == 0 )
         color=5;  
      else if( type.bg == -1 )
         color=6;
      else if( type.bg == 1 )
         color=7;
      else if( type.bg == 2 )
         color=8;
   }
   else if( type.bg == 0 ) 
      color=1;
   else if( type.bg == -1 )
      color=2;
   else if( type.bg == 1 )
      color=3;
   else if( type.bg == 2 )
      color=4;

   wattron(map,COLOR_PAIR(color));
    //if the foreground isn't blank (water)
    if( type.fg != ' ' )
   {
       //should be ' ' foreground
      mvwaddch(map,y,x,type.fg); 
      mvwaddch(map,y,x+1,type.fg);
      mvwaddch(map,y,x+2,type.fg);
      mvwaddch(map,y+1,x,type.fg);
      mvwaddch(map,y+1,x+1,type.fg);
      mvwaddch(map,y+1,x+2,type.fg);
   }
   else
   {
       //set colors of 2x2 area
      mvwaddch(map,y,x,ACS_ULCORNER); 
      mvwaddch(map,y,x+1,ACS_HLINE);
      mvwaddch(map,y,x+2,ACS_URCORNER);
      mvwaddch(map,y+1,x,ACS_LLCORNER);
      mvwaddch(map,y+1,x+1,ACS_HLINE);
      mvwaddch(map,y+1,x+2,ACS_LRCORNER);
   }
   wattroff(map,COLOR_PAIR(color));
}

void WMap::gridMark(
                      int y,
                      int x,
                      int type
                   )
{
    //overwrite grid value
   grid[y][x].bg=type; 
    //update window to display new grid
   wUpdate(); 
}

void WMap::addPoint(
                     WBox& echoBox,
                     int &y,
                     int &x
                   )
{
   echoBox.print("use arrow keys to move cursor, press 'A' to accept target",
                 'c');
    //reference to the grid we will overwrite 
    //used for checking valid ship writing
   marker reference[10][10]; 
    //intermediary for transferring between states
   marker buffer[10][10]; 
   copy(grid,buffer);
    //store cursor location
   int cX=0;
   int cY=0;
    //store change of cursor location
   int dX=0;
   int dY=0;
   bool input=true;
   bool validMove=false;
   int press;
   grid[cY][cX].fg='#';
   wUpdate();
    //while still taking in info from user
   while( input ) 
   {
       //while not accepting a move
      while( ( press=wgetch(stdscr) ) != 'A' ) 
      {
         if( press == KEY_LEFT )
         {
             //if valid move
            if( checkBounds(cY,cX-1) )
            {
                dX=-1;
                dY=0;
                validMove=true;
            }
         }
         else if( press == KEY_RIGHT )
         {
            if( checkBounds(cY,cX+1) )
            {
               dX=1;
               dY=0;
               validMove=true;
            }
         }
         else if( press == KEY_UP )
         {
            if( checkBounds(cY-1,cX) )
            {
               dY=-1;
               dX=0;
               validMove=true;
            }
         }
         else if( press == KEY_DOWN )
         {
            if( checkBounds(cY+1,cX) )
            {
               dY=1;
               dX=0;
               validMove=true;
            }
         }
          //with move info and validation...
         if( validMove ) 
         {
            grid[cY][cX].fg=buffer[cY][cX].fg;
             //store new intermediary
            copy(grid,buffer); 
            cX+=dX;
            cY+=dY;
            grid[cY][cX].fg='#';
             //display new state
            wUpdate(); 
         }
          //reset to ensure user inputs valid character
         validMove=false;       
      }
       //if the user didn't select a water square to target
      if( grid[cY][cX].bg != 0 ) 
      {
          //print the message that they cannot select that square
         echoBox.print("ERROR: select a square that you haven't already tried! ",
                       'l');
          //user still needs to select a square
         input=true; 
      }
      else
        //user has successfully selected a square
       input=false; 
   }
   grid[cY][cX].fg=' ';
   wUpdate();
   y=cY;
   x=cX;
}

void WMap::copy(
                  marker rGrid[][10],
                  marker wGrid[][10]
               )
{
   for( int r = 0 ; r < 10 ; r++ )
   {
      for( int c = 0 ; c < 10 ; c++ )
      {
          //equate the two arrays
         wGrid[r][c]=rGrid[r][c]; 
      }
   }
return;
}

bool WMap::checkBounds(
                         int cY,
                         int cX
                      )
{
   if( cX > 9 || cX < 0 || cY > 9 || cY < 0 )
      return(false);
   else
      return(true);
}

void WMap::placeShip(
                       WBox& echoBox,
                       ShipClass* ship
                    )
{
   echoBox.print("use arrows to move, 'r' to rotate, and 'A' to accept placement",
                 'c');  
    //get the size of the ship (number of grid squares)
   int size=ship->getHP();
    //store the name of the ship in a string
   std::string shipName=ship->getName();
    //grab the first letter of the ship's name and store it in a char
   char code=shipName.at(0);
    //store and initialize the orientation of the ship
   bool vert=true; 
   int cX=0;
   int cY=0;
   int dX=0;
   int dY=0;
   int dVert=false;
    //status of still getting input
   bool input=true; 
    //status of move choice
   bool valid=false; 
    //store keypress
   int press; 
    //store the original setup of the map to reference\
    //in case of overlaying one ship on another
   marker reference[10][10]; 
    //store original map before modifications
   copy(grid,reference); 
    //begin by placing the ship at origin
   putShipCursor(cY,cX,vert,size); 
    //update the window
   wUpdate(); 
    //while still getting input from user
   while(input) 
   {
       //while user is still manipulating the ship movement
      while( ( press=wgetch(stdscr) ) != 'A' ) 
      {
         if( press == KEY_LEFT )
         {
             //if valid move
            if( checkBounds(cY,cX-1,vert,size) )
            {
                dX=-1;
                dY=0;
                dVert=false;
                valid=true;               
            }
         }
         else if( press == KEY_RIGHT )
         {
            if( checkBounds(cY,cX+1,vert,size) )
            {
               dX=1;
               dY=0;
               dVert=false;
               valid=true;
            }
         }
         else if( press == KEY_UP )
         {
            if( checkBounds(cY-1,cX,vert,size) )
            {
               dY=-1;
               dX=0;
               dVert=false;
               valid=true;
            }
         }
         else if( press == KEY_DOWN )
         {
            if( checkBounds(cY+1,cX,vert,size) )
            {
               dY=1;
               dX=0;
               dVert=false;
               valid=true;
            }
         }
         else if( (char)press == 'r' )
         {
            if( checkBounds(cY,cX,!vert,size) )
            {
               dY=0;
               dX=0;
               dVert=true;
               valid=true;
            }
         } 
          //with move info and validation...
         if( valid ) 
         {
             //remove the old ship location from the grid
            replaceCursor(reference,grid,cY,cX,vert,size);
            cX+=dX;
            cY+=dY;
            if( dVert )
               vert=!vert;
             //place new ship on grid
            putShipCursor(cY,cX,vert,size); 
             //update window
            wUpdate(); 
         }
          //reset to ensure user inputs valid character
         valid=false; 
      }
      //perform checks to see if move can be accepted
      if( checkOverlap(reference,cY,cX,vert,size) )
         input=false;
      else
         echoBox.print("ERROR: cannot overlap ships!",'l');
   }
    //remove the highlighting over the ship
   unhighlight(cY,cX,vert,size,code); 
    //store data about the ship location
   ship->setLoc(cY,cX,vert); 
   wUpdate();
}

void WMap::putShipCursor(
                           int hY,
                           int hX,
                           bool vert,
                           int size
                        )
{
   if( vert )
   {
      for( int r=0 ; r < size ; r++ )
      {
         grid[hY+r][hX].fg='#';
         grid[hY+r][hX].bg=2;
      }
   }
   else
   {
      for( int c=0 ; c < size ; c++ )
      {
         grid[hY][hX+c].fg='#';
         grid[hY][hX+c].bg=2;
      }
   }
}

void WMap::replaceCursor(
                           marker rGrid[][NUM_MAX_COLS],
                           marker wGrid[][NUM_MAX_COLS],
                           int hY,
                           int hX,
                           bool vert,
                           int size
                        )
{
   if(vert)
   {
      for( int r=0 ; r < size ; r++ )
      {
         wGrid[hY+r][hX].fg=rGrid[hY+r][hX].fg;
         wGrid[hY+r][hX].bg=rGrid[hY+r][hX].bg;
      }
   }
   else
   {
      for( int c=0 ; c < size ; c++ )
      {
         wGrid[hY][hX+c].fg=rGrid[hY][hX+c].fg;
         wGrid[hY][hX+c].bg=rGrid[hY][hX+c].bg;
      }
   }  
}

bool WMap::checkBounds(
                         int hY,
                         int hX,
                         bool vert,
                         int size
                      )
{
   if(vert)
   {
      if( hY < 0 || ( hY + size -1 ) > 9 || hX < 0 || hX > 9)
         return(false);
   }
   else
   {
      if( hY < 0 || hY > 9 || hX < 0 || ( hX + size -1 ) > 9 )
         return(false);
   }
}

bool WMap::checkOverlap(
                          marker rGrid[][NUM_MAX_COLS],
                          int hY,
                          int hX,
                          bool vert,
                          int size
                       )
{
   if(vert)
   {
      for( int r=0 ; r < size ; r++ )
      {
          //if there is already a ship there
         if( rGrid[hY+r][hX].bg == 2 ) 
            return(false);
      }
   }
   else
   {
      for( int c=0 ; c < size ; c++ )
      {
         if( rGrid[hY][hX+c].bg == 2 )
            return(false);
      }
   }
    //if all checks passed
   return(true); 
}

void WMap::unhighlight(
                         int hY,
                         int hX,
                         bool vert,
                         int size,
                         char code
                      )
{
   if( vert )
   {
      for( int r=0 ; r < size ; r++ )
         grid[hY+r][hX].fg=code;
   }
   else
   {
      for( int c=0 ; c < size ; c++ )
         grid[hY][hX+c].fg=code;
   }
}

