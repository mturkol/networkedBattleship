/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         GUIGLOBALCONSTANTS.h
 Description:		Global constats used by the game
 ******************************************************************************/
 
#ifndef GUIGLOBALCONSTANTS_H
#define GUIGLOBALCONSTANTS_H

#include <string>
using namespace std;

 //screen size requirements
const int ROWSREQ=35+1; 
const int COLSREQ=82;

 //ally map x (UL)
const int AMAPX=48; 
 //ally map y
const int AMAPY=1+1; 
  //height
const int AMAPH=22;
 //width
const int AMAPW=32; 

 //enemy
const int EMAPX=1; 
const int EMAPY=1+1;
const int EMAPH=22;
const int EMAPW=32;

 //echo box
const int EBOXX=0; 
const int EBOXY=30+1;
const int EBOXH=5;
const int EBOXW=82;

 //ally list
const int ALISTX=48; 
const int ALISTY=23+1;
const int ALISTH=7;
const int ALISTW=32;

 //enemy list
const int ELISTX=1; 
const int ELISTY=23+1;
const int ELISTH=7;
const int ELISTW=32;

 //map marker width (chars)
const int MMW=3; 
 //height
const int MMH=2; 

 //max. #rows on the map grid
const int NUM_MAX_ROWS = 10; 
 //min. #columns on the map grid
const int NUM_MAX_COLS = 10; 
 //# ships to play the game with
const int NUM_SHIPS = 5;
//length of an aircraft
const int LENGTH_AIRCRAFT = 5;
//length of a battleship
const int LENGTH_BATTLESHIP = 4;
//length of a destroyer
const int LENGTH_DESTROYER = 3;
//length of a submarine
const int LENGTH_SUBMARINE = 3;
//length of a patrolship
const int LENGTH_PATROLSHIP = 2;
//Marker type representing a miss
const int MISS_MARKER = -1;
//Marker type representing plain empty water
const int EMPTY_MARKER = 0;
//Marker type representing a hit
const int HIT_MARKER = 1;
//Marker type representing a ship occupying the marker
const int SHIP_MARKER = 2;
//Default Ship Identifier that maps to no ship.
const char NO_SHIP_ID = 'n';
//Ship Identifier that maps to an Aircraft Carrier.
const char AIRCRAFT_CARRIER_ID = 'a';
//Ship Identifier that maps to a Battleship.
const char BATTLESHIP_ID = 'b';
//Ship Identifier that maps to a Submarine.
const char SUBMARINE_ID = 's';
//Ship Identifier that maps to an Destroyer.
const char DESTROYER_ID = 'd';
//Ship Identifier that maps to a Patrol Ship.
const char PATROL_SHIP_ID = 'p';
//Character representing the create new game choice
const int CREATE_GAME_OPTION = 1;
//Character representing the join game choice
const int JOIN_GAME_OPTION = 2;
//Character representing the play against cpu choice
const int PLAY_CPU_OPTION = 3;
//Character representing the play against cpu choice
const int EXIT_OPTION = 4;
//Total score for hitting ships that decides the win case
const int SCORE_LIMIT = LENGTH_AIRCRAFT + LENGTH_BATTLESHIP + LENGTH_SUBMARINE
                        + LENGTH_DESTROYER + LENGTH_PATROLSHIP;

//GLOBAL CONSTANTS THAT ARE USED BY THE AI CLASS
const int NUM_MIN_ROWS = 0;
const int NUM_MIN_COLS = 0;

//Markes for the AI Maps 
const int BOMB = 1;
const int HIT = 2;
const int EMPTY = 0;

//Int value representing a specific direction
const int UP = 0; 
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

//Strings to identify the different possible moves by the AI
const string HUNT_SHIP = "Hunt Ship";
const string FIND_DIREC = "Find Direc";
const string SINK_SHIP = "Sink Ship";
const string SINK_OPP = "Sink Opp";

#endif
