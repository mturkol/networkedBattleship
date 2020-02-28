/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WindowClass.cpp
 Description:	
 ******************************************************************************/

#include "WindowClass.h"

void WindowClass::refresh(
                         )
{
   wrefresh(map);
}

WINDOW* WindowClass::getWindow(
                              )
{
   return(map);
}
