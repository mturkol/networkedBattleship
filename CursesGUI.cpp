/******************************************************************************
 Date:              4/17/2014
 Author:            Alexander Vaughn
 File name:         CursesGUI.cpp
 Description:       Class that manages all the GUI of the game
 ******************************************************************************/

#include "CursesGUI.h"
#include "GUIGLOBALCONSTANTS.h"
#include "WindowClass.h"
#include <string.h>
#include <sstream>

CursesGUI::CursesGUI(
                    )
{
   initscr();
   noecho();
   //allow extended character implementation by terminal
   cbreak(); 
   //begin mode to allow color input
   start_color(); 
   init_pair(1,COLOR_CYAN,COLOR_BLUE);
   init_pair(2,COLOR_CYAN,COLOR_WHITE);
   init_pair(3,COLOR_CYAN,COLOR_RED);
   init_pair(4,COLOR_CYAN,COLOR_YELLOW);
   init_pair(5,COLOR_MAGENTA,COLOR_BLUE);
   init_pair(6,COLOR_MAGENTA,COLOR_WHITE);
   init_pair(7,COLOR_MAGENTA,COLOR_RED);
   init_pair(8,COLOR_MAGENTA,COLOR_YELLOW);
   char ch;
    //make cursor invisible
    curs_set(0); 
    //enable non-char keys
    keypad(stdscr,TRUE); 
    int rowMax,colMax;
    //get total terminal size
    getmaxyx(stdscr,rowMax,colMax); 
    //if terminal window isn't large enough
    while( rowMax < ROWSREQ || colMax < COLSREQ ) 
	{
		clear();
		refresh();
		mvprintw(0,0,"ERROR: WINDOW TOO SMALL");
		mvprintw(1,0,"resize terminal window and try again");
		mvprintw(2,0,"press 'R' to try again");
		refresh();
		bool status=FALSE;
		while( !status )
		{
			if( ( ch = getch() ) == 'R' )
				status=TRUE;
		}
		getmaxyx(stdscr,rowMax,colMax);
		move(0,0);
   }
   clear();
   refresh();
   std::stringstream ss;
   std::string buffer;
   for(int index=0;index<10;index++)
   {
      ss.clear();
      ss.str("");
      ss << index;
      ss >> buffer;
      mvprintw((index+1)*MMH+1,0,buffer.c_str());
      mvprintw((index+1)*MMH+1,47,buffer.c_str());
      mvprintw(1,(index+1)*MMW,buffer.c_str());
      mvprintw(1,(index+1)*MMW +47,buffer.c_str());
   }
/*
   for(int y=0;y<10;y++)
   {
      ss.clear();
      ss.str("");
      ss << y;
      ss >> buffer;
      mvprintw((y+1)*MMH,47,buffer.c_str());
   }
*/   
   refresh();
 
   allyMap.init(AMAPH,AMAPW,AMAPY,AMAPX);
   enemyMap.init(EMAPH,EMAPW,EMAPY,EMAPX);
   echoBox.init(EBOXH,EBOXW,EBOXY,EBOXX);
   allyList.init(ALISTH,ALISTW,ALISTY,ALISTX,'a');
   enemyList.init(ELISTH,ELISTW,ELISTY,ELISTX,'e');
   allyMap.wUpdate();
   enemyMap.wUpdate();
   mvprintw(0,11,"ENEMY MAP");
   mvprintw(0,60,"ALLY MAP");

   refresh();
   allyMap.refresh();
   enemyMap.refresh();
   echoBox.refresh();
   allyList.refresh();
   enemyList.refresh();
    //reset cursor to 'home' position

   move(0,0);
}

CursesGUI::~CursesGUI(
                     )
{
    //necessary to return full control to terminal after termination
   endwin();
}

//Print to last communication box
void CursesGUI::pLComm(
                         std::string str
                      )
{
   echoBox.print(str,'l');
}

//Print to current orders box
void CursesGUI::pCOrd(
                        std::string str
                     )
{
   echoBox.print(str,'c');
}

void CursesGUI::allyLMark(
                            const char type
                         )
{
  allyList.mark(type); 
}

void CursesGUI::enemyLMark(
                             const char type
                          )
{
   enemyList.mark(type);
}

void CursesGUI::allyMMark(
                             int y,
                             int x
                         )
{
      allyMap.gridMark(y,x,1);
      allyMap.refresh();
}

void CursesGUI::enemyMMark(
                             int y,
                             int x,
                             int type
                          )
{
   if( type == -1 || type == 1 )
   {
      enemyMap.gridMark(y,x,type);
      enemyMap.refresh();
   }
}

void CursesGUI::getTarget(
                            int &y,
                            int &x
                         )
{
    //gets user to use arrow keys to select point graphically
    //also sends out instructions and warnings through the echoBox windows
   enemyMap.addPoint(echoBox,y,x);
   echoBox.print("Wait for opponent...", 'c');
}

void CursesGUI::placeShips(
                             ShipClass* shipArray[NUM_SHIPS]
                          )
{
   for( int ID = 0 ; ID < NUM_SHIPS ; ID++ )
   {
       //setup the map for each ship (one at a time) 
       //this is passing pointers to each ship
      allyMap.placeShip(echoBox,shipArray[ID]);
      echoBox.print("Wait for opponent...",'c');
   }
}

void CursesGUI::Break()
{
   endwin();
    //deallocate memory associated with the windows
   delwin(allyMap.getWindow());
   delwin(enemyMap.getWindow());
   delwin(echoBox.getWindow());
   delwin(allyList.getWindow());
   delwin(enemyList.getWindow());
   delwin(stdscr);
}
