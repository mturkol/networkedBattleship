/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         ClientClass.cpp
 Description:		Header file for class that manages the Client side of the 			
 					connection to play a game via the network
 ******************************************************************************/

#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H

#include "ClientSocket.h"
#include <string>
#include <unistd.h>

class ClientClass
{
   public:
       //initializer queries user for server IP address and makes connection
       //returns 'false' on failure to connect
      bool initClientClass();
       //sends two chars to the other user in a whitespace seperated string
       //via the connected sockets
      void sendResponse(char a, char b);
       //function waits for and interprets response from other user and stores
       //the two returned chars via the passed reference
       //(note that coordinates only go up to 9, so we are able to fully
       //send coordinates via chars)
      void getResponse(char &a, char &b);

   private:
      ClientSocket clientSock;
       //listens for other user to return a string back via the socket
};

#endif 
