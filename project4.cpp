//============================================================================
// Name        : project4.cpp
// Author      : Mert Turkol
// Version     : 3.3
// Copyright   : GNU General Public License
// Description : Implements a turn-based Networked BattleShip game using
//               socket programming principles. The game can be played either
//               between two remote players using client-server communication
//               or against the computer AI as a single player.
//============================================================================

#include <ncurses.h>
#include <iostream>
#include <time.h>
#include "ControlClass.h"
#include "MarkerClass.h"
#include "CursesGUI.h"
#include "ShipClass.h"
#include "GUIGLOBALCONSTANTS.h"
#include "ServerClass.h"
#include "ClientClass.h"
#include "AIClass.h"
#include "getCreateJoinGameChoice.h"
using namespace std;

int main()
{
  //Create the game engine controller
  ControlClass gameController;

  //Greet the player with the welcome screen
  gameController.greetPlayers();

  //create a server object in case the player chooses to be a server
  ServerClass gameServer; //just declared, not initialized

  //create a client object in case the player chooses to be a client
  ClientClass gameClient; //just declared, not initialized

  //create a computer AI object in case the player chooses to play against
  //the computer
  AIClass gameAI;
  
  bool runGame = true;
  while(runGame)
  {
    //Get input from players on whether they want to create a networked game,
    //join a game created by someonelse as a client or play against the computer
    //AI
    int gameTypeChoice = getCreateJoinGameChoice();

    //If the player is a server, create a server and initiate it to wait for
    // a connection
    if (gameTypeChoice == CREATE_GAME_OPTION) //when the player is the server
    {
      //initialize the server
      if(!gameServer.initServerClass())
      return(1); //immediately exit due to socket initialization failure
    }
    else if (gameTypeChoice == JOIN_GAME_OPTION) //when the player is a client
    {
      //initialize client
      if(!gameClient.initClientClass())
      return(1); //immediately exit due to socket initialization failure
    }
    //when the game is against the PC
    else if (gameTypeChoice == PLAY_CPU_OPTION)
    {
      //initialize the the computer's artificial intelligence
      gameAI.initAI();
    }
    //when the player wants to quit the program
    else if (gameTypeChoice == EXIT_OPTION)
    {
      cout << "Thank you for playing NETWORK BATTLESHIPS!" << endl;
      return (0);
    }
    bool wantToReplay = true; //checks if the player wants to replay the game

    //either the first game played or the player wanted to replay the game.
    while (wantToReplay) 
    {
      //initialize the ally map grid with 0 markers (plain empty water)
      MarkerClass** myAllyGrid;
      gameController.initGrid(myAllyGrid);
    
      //Create the ncurses GUI to be used for gameplay
      CursesGUI myGUI;

      //Create the navy of a player and put them into an array so that the 
      //player can place the ship items pointed by the array's elements to the 
      //ally map
      ShipClass* myNavyArry[NUM_SHIPS];
      gameController.setShipArray(myNavyArry);

      //Allow the player to place the ships making up his navy on his GUI map
      //Pass the created shipArray to the GUI for the player to place his ships
      myGUI.placeShips(myNavyArry);

      //Update the ally marker grid according to the ship placement undertaken
      //in GUI part by the player
      gameController.getShipsAndSetGrid(myNavyArry, myAllyGrid);

      //when the player has chosen to create a new game to host it as a server
      if(gameTypeChoice == CREATE_GAME_OPTION)
      {
        //loop until one of the players destroys the others entire navy
        while((gameController.getEnemyScore() < SCORE_LIMIT)
              && (gameController.getNumHits() < SCORE_LIMIT))
        {
          //attack the other player
          //It's player's turn
          gameController.attackEnemy(myGUI,gameServer);
          //when the player hasn't destroyed the enemy's entire navy

          if (gameController.getNumHits() < SCORE_LIMIT)
          {
            //get into defense position and wait for the enemy's attack
            //It's the enemy's turn
            gameController.defendAlly(myAllyGrid,
                                      myGUI,
                                      myNavyArry,
                                      gameServer);
          }//end of if-player didn't win case
        }//end of while opponent hasn't won
      }//end of if-player is server case
      else if (gameTypeChoice == JOIN_GAME_OPTION) //when the player is a client
      {
        //loop until one of the players destroys the others entire navy
        while((gameController.getNumHits() < SCORE_LIMIT)
              && (gameController.getEnemyScore() < SCORE_LIMIT))
        {
          //get into defense position and wait for the enemy's attack
          //It's enemy's turn
          gameController.defendAlly(myAllyGrid,
                                    myGUI,
                                    myNavyArry,
                                    gameClient);

          //when the enemy still hasn't destroyed the players's entire navy
          //It's player's turn
          if (gameController.getEnemyScore() < SCORE_LIMIT)
          {
            //attack the other player
            gameController.attackEnemy(myGUI,
                                       gameClient);
          }//end-of enemy win check case
        }//end of player loop
      }//end of if-player is client case
      //when the player is playing against the computer AI
      else if(gameTypeChoice == PLAY_CPU_OPTION)
      {
        //initialize the computer map grid with 0 markers (plain empty water)
        MarkerClass** cpuGrid;
        gameController.initGrid(cpuGrid);

        //Create the navy of the computer and put them into an array so that
        //the computer can randomly place the ship items pointed by the array's
        //elements to its artificial cpu map
        ShipClass* cpuShipsArry[NUM_SHIPS];
        gameController.setShipArray(cpuShipsArry);

        //Make the computer randomly place its ships on its own map using
        //randomized number generators
        gameAI.placeShips(cpuShipsArry);
        //Update the CPU marker grid according to the computer's randomized ship
        //placement undertaken
        gameController.getShipsAndSetGrid(cpuShipsArry, cpuGrid);

        //loop until either the player or the computer destroys the other's navy
        while((gameController.getEnemyScore() < SCORE_LIMIT)
              && (gameController.getNumHits() < SCORE_LIMIT))
        {
          //Human's turn, attack the computer
          gameController.attackAI(myGUI, cpuGrid, cpuShipsArry);
          //when the player couldn't destroy the enemy's entire navy
          //now computer takes turn
          if (gameController.getNumHits() < SCORE_LIMIT)
          { 
            sleep(2); //make the computer wait for two seconds before taking
            //action. Makes it easier to visualize what the last move of the
            //computer was. 
            //get into defense position and wait for the enemy's attack
            gameController.attackHuman(gameAI,
                                       myGUI,
                                       myAllyGrid,
                                       myNavyArry);
          }//end of if-player didn't win case
        }//end of while computer or the player hasn't won
      }//end of if-playing against the computer AI

      //Inform the player on whether he won or lost. Print his statistics
      gameController.printStats(myGUI);
      
      //Ask the player if he want a replay or if he wants to quit
      wantToReplay = gameController.getReplayChoice(myGUI);
      
      //free dynamically allocated space for the pointers within the ship array
      gameController.deleteShips(myNavyArry);
      
      //free dynamically allocated space for the marker grid
      gameController.deleteAllyGrid(myAllyGrid);
    
    }//end-of want-To-Replay loop case
  }
  return 0;
}
