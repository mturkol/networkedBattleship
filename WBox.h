/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WBox.h
 ******************************************************************************/
 
#ifndef WBOX_H
#define WBOX_H
#include <ncurses.h>
#include <string.h>
#include <string>
#include "GUIGLOBALCONSTANTS.h"
#include "WindowClass.h"


class WBox: public WindowClass
{
   public:
       //initialize everything for the window
      void init(
                  int height,
                  int width,
                  int starty,
                  int startx
               ); 
      //print cstring to echo box. Type requires either 'l' or 'c'
      //to print to "LAST" or "CURRENT" section 
     void print(
                   std::string str,
                   char type
                );
};
#endif
