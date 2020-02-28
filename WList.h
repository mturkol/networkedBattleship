/******************************************************************************
 Student Name:      Alexander Vaughn
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WList.h
 Description:	     Implementation interface for list of ships on the screen
 ******************************************************************************/

#ifndef WLIST_H
#define WLIST_H
#include <ncurses.h>
#include "WindowClass.h"

class WList: public WindowClass
{
   public:
       //initialize window
      void init(
                  int height,
                  int width,
                  int starty,
                  int startx,
                  char type
               ); 
       //take passed ship identifier and check box for sunk
      void mark(
                  const char type
               ); 
};
#endif
