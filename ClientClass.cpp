/******************************************************************************
 Student Name:      
 Last Edit:         4/15/2014
 Class:             EECS 402 W14
 File name:         ClientClass.cpp
 Description:		Manages the Client side of the connection to play a game via
 					the network
 ******************************************************************************/
#include "ClientClass.h"
#include "ClientSocket.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

bool ClientClass::initClientClass(
                                 )
{
   string IPADDR;
   std::cout << "input IP address of server...\n";
   std::cin >> IPADDR;
   std::cout << "attempting to connect to the server...\n";
    //return the status of connecting to the server
   return(clientSock.connectToServer(IPADDR,30003));
}

void ClientClass::sendResponse(
                                 char a,
                                 char b
                              )
{
   ostringstream oss;
   oss.clear();
   oss.str("");
   oss << a << " " << b;
   clientSock.sendStr(oss.str());
}

void ClientClass::getResponse(
                                char &a,
                                char &b
                             )
{
   istringstream iss;
   string response;
    //listens until the other user sends a string
   clientSock.recvStr(response); 
   iss.clear();
   iss.str(response);
    //store the sent inputs in the passed by reference chars
   iss >> a >> b;
}
