/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         ServerClass.h
 Description:		Manages the server side of the networked game between two 
 					players
 ******************************************************************************/
 
#ifndef SERVERCLASS_H
#define SERVERCLASS_H

#include "ServerSocket.h"

class ServerClass
{
   public:
       //initializes the server socket and waits for the client user to
       //make a successfull connection before continuing
       //returns false upon failure or timeout
      bool initServerClass();
       //sends two chars to the other user in a whitespace separated string
       //via the connected sockets
      void sendResponse(char a, char b);
       //function waits for and interprets response from other user and stores
       //the two returned chars via the passed reference
       //(note that coordinates only go up to 9, so we are able to fully
       //send coordintes via chars)
      void getResponse(char &a, char &b);

   private:
      ServerSocket serverSock;
       //listens for other user to return a string back via the socket
      ServerSocket sockToAccept;
};

#endif
