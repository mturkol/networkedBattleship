/******************************************************************************
 Student Name:      Alexander Vaughn
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WindowClass.h
 ******************************************************************************/
#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include <ncurses.h>

class WindowClass
{
   public:
       //refresh this window
      void refresh(
                  ); 
       //return pointer to WINDOW struct
      WINDOW* getWindow(
                       ); 
   
   protected:
       //pointer to the map type
      WINDOW *map; 
       //the extents of the window that we can write to
      int xEnd,yEnd; 

   private:
};
#endif
