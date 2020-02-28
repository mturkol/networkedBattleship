/******************************************************************************
 Student Name:      Alexander Vaughn 
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WList.cpp
 ******************************************************************************/
 
#include "WList.h"
#include "GUIGLOBALCONSTANTS.h"

void WList::init(
                   int height,
                   int width,
                   int starty,
                   int startx,
                   char type
                )
{
   map=newwin(height,width,starty,startx);
   for( int r = 1 ; r <= NUM_SHIPS ; r++ )
   {
      mvwprintw(map,r,0,"[");
      mvwprintw(map,r,2,"]");
   }
   if( type == 'a' )
      mvwprintw(map,0,0,"ALLY SHIPS SUNK");
   if( type == 'e' )
      mvwprintw(map,0,0,"ENEMY SHIPS SUNK");
   mvwprintw(map,1,4,"Aircraft Carrier");
   mvwprintw(map,2,4,"Battleship");
   mvwprintw(map,3,4,"Destroyer"); 
   mvwprintw(map,4,4,"Submarine");
   mvwprintw(map,5,4,"Patrol Ship");
}

void WList::mark(
                   const char type
                )
{
   int row;
   if( type == 'a' )
      row=1;
   else if( type == 'b' )
      row=2;
   else if( type == 'd' )
      row=3;
   else if( type == 's' )
      row=4;
   else if( type == 'p' )
      row=5;
   else
      return;
   mvwaddch(map,row,1,'X');
   refresh();
}
