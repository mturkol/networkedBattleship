/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         WBox.cpp
 Description:	
 ******************************************************************************/

#include "WBox.h"

void WBox::init(
                  int height,
                  int width,
                  int starty,
                  int startx
               )
{
   map=newwin(height,width,starty,startx);
   mvwprintw(map,0,1,"LAST COMMUNICATION");
   mvwprintw(map,3,1,"CURRENT ORDERS");
}

void WBox::print(
                   std::string str,
                   char type
                )
{

    //convert 'string' to 'char*' process
   char* buffer=new char[str.size()+1]; 
   std::copy(str.begin(),str.end(),buffer);
   buffer[str.size()]='\0';
    //write to LAST area of box
   if(type=='l') 
   {
       //set cursor on output line
      wmove(map,1,0); 
       //clear to the end of line
      wclrtoeol(map); 
       //print new string
      wprintw(map,buffer); 
       //refresh that window
      refresh(); 
   }
    //write to CURRENT area of box
   if(type=='c') 
   {
      wmove(map,4,0);
      wclrtoeol(map);
      wprintw(map,buffer);
      refresh();
   }
   delete[] buffer;
}
