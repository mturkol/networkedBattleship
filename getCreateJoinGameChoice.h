/*
 * getCreateJoinGameChoice.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Mert Turkol
 * Description: Gets input from the user regarding the main menu choice
 */

#ifndef GETCREATEJOINGAMECHOICE_H_
#define GETCREATEJOINGAMECHOICE_H_

#include <iostream>
#include <string>
#include "GUIGLOBALCONSTANTS.h"
using namespace std;

int getCreateJoinGameChoice()
{
  cout << endl; //put a newline for visual clarity

  int gameOption; //to be returned by the input function to decide whether
  //a player is going to be a server or a client
  bool validMenuChoice = false; //hold information on whether the player chose
  //a valid main menu choice regarding creating a new game or joining a game
  int playerMenuChoice;

  while(!validMenuChoice)
  {
    //print to screen the options player can choose for playing the game
    cout << "Please choose one of the options below:" << endl;
    cout << "1. Create a new BattleShip game" << endl;
    cout << "2. Join a BattleShip game" << endl;
    cout << "3. Play against CPU" << endl;
    cout << "4. Exit game" << endl;

    cin >> playerMenuChoice; //get input from the player's keyboard

    if (cin.fail() ||
        (playerMenuChoice < CREATE_GAME_OPTION) ||
        (playerMenuChoice > EXIT_OPTION))
    {
      cin.clear(); //take the input stream out of fail state
      cin.ignore(200, '\n'); //allow new data to be consumed in the future
      cout << "Error! "
           << "Please enter:" << endl
           << "'1' if you want to host a new game as a server "<< endl
           << "'2' if you want to join a game as a client" << endl
           << "'3' if you want to play against CPU" << endl
           << "'4' if you want to exit the game" << endl;
    }
    else
    {
      validMenuChoice = true;
    }
  }
  cout << endl; //put a new line
  if (playerMenuChoice == CREATE_GAME_OPTION) //the player is going to host
  {
    gameOption = CREATE_GAME_OPTION;
  }
  else if (playerMenuChoice == JOIN_GAME_OPTION) //the player is going to be 
  //the client
  {
    gameOption = JOIN_GAME_OPTION;
  }
  else if (playerMenuChoice == PLAY_CPU_OPTION) //the player is going to play 
  //against the computer
  {
    gameOption = PLAY_CPU_OPTION;
  }
  else if (playerMenuChoice == EXIT_OPTION) //when the player is exiting
  {
    gameOption = EXIT_OPTION;
  }

  return gameOption; //return the status of the player being whether a server
                   //that gosts a new game or a client that joins a game
}

#endif /* GETCREATEJOINGAMECHOICE_H_ */
