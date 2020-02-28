/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         ServerClass.cpp
 Description:		Manages the server side of the networked game between two 
 					players
 ******************************************************************************/
 
#include "ServerClass.h"
#include <string>
#include <iostream>
#include <sstream>

bool ServerClass::initServerClass(
                                 )
{

   int portNum= 30003;
   bool isConnected=false;
   std::cout << "Server binding to port " << portNum << std::endl;
   if(sockToAccept.bindToPort(portNum))
   {
      std::cout << "Server awaiting client connection" << std::endl;
      if (sockToAccept.waitForConnection(serverSock))
      {
         std::cout << "Got client connection" << std::endl;
         isConnected=true;
      }
   }
    //return the status of the connection attempt
    //will return false upon timeout or connection error
   return(isConnected);
}

void ServerClass::sendResponse(
                                 char a,
                                 char b
                              )
{
   ostringstream oss;
   oss.clear();
   oss.str("");
   oss << a << " " << b;
   serverSock.sendStr(oss.str());
}

void ServerClass::getResponse(
                                char &a,
                                char &b
                             )
{
   istringstream iss;
   string response;
    //listens until the other user sends a string
   serverSock.recvStr(response);
   iss.clear();
   iss.str(response);
    //store the sent inputs in the passed by reference chars
   iss >> a >> b;
}
