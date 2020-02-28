/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         ServerSocket.h
 ******************************************************************************/

#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#include "Socket.h"

class ServerSocket: public Socket
{
  public:
    ServerSocket():Socket()
    {
      ; //nothing needed
    }

    bool bindToPort(int inPortNum)
    {
      sockaddr_in sockAddr;
      int result;
      bool success;

      success = true;

      sockAddr.sin_family = AF_INET;
      sockAddr.sin_addr.s_addr = INADDR_ANY;
      sockAddr.sin_port = inPortNum;

      result = bind(sock, (struct sockaddr*) &sockAddr, sizeof(sockAddr));

      if (result == -1)
      {
        cout << "ERROR: Could not bind to port " << inPortNum << endl;
        success = false;
      }

      return success;
    }

    bool waitForConnection(ServerSocket &connectedSock)
    {
      struct sockaddr_in clientAddr;
      socklen_t clientAddrSize;
      bool success;

      success = true;
      listen(sock, 5);
      connectedSock.sock = accept(sock, (struct sockaddr*)&clientAddr,
                             &clientAddrSize);

      if (connectedSock.sock < 0)
      {
        cout << "ERROR on connection!" << endl;
        success = false;
      }

      return success;
    }
};

#endif // _SERVERSOCKET_H_
