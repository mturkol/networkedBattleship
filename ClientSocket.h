/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         ClientSocket.h
 ******************************************************************************/
 
#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

#include "Socket.h"

class ClientSocket: public Socket
{
  public:
    ClientSocket():Socket()
    {
      ; //nothing needed
    }

    bool connectToServer(string serverLocIn, int portNumIn)
    {
      struct sockaddr_in serverAddr;
      bool success;
      int result;
      success = true;

      serverAddr.sin_family = AF_INET;
      serverAddr.sin_port = portNumIn;

      inet_pton(AF_INET, serverLocIn.c_str(), &serverAddr.sin_addr);

      result = connect(sock, (struct sockaddr*)&serverAddr,
                             sizeof(serverAddr));

      if (result < 0)
      {
        cout << "ERROR on connection to server!" << endl;
        success = false;
      }

      return success;
    }
};

#endif // _CLIENTSOCKET_H_
