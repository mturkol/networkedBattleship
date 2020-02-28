/******************************************************************************
 Student Name:      
 Last Edit:         4/17/2014
 Class:             EECS 402 W14
 File name:         Socket.h
 Description:		Manages the server side of the networked game between two 
 					players
 ******************************************************************************/
 
#ifndef _SOCKET_H_
#define _SOCKET_H_

#define MAX_MSG_SIZE 256

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

class Socket
{
  protected:
    int sock;

  public:
    Socket()
    {
      sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    bool sendStr(const string &val)
    {
      int numWrote;
      bool success;

      success = true;

      numWrote = write(sock, val.c_str(), val.length() + 1);

      if (numWrote != val.length() + 1)
      {
        cout << "ERROR Tried to write " << val.length() << " but only wrote "
             << numWrote << endl;
        success = false;
      }

      return success;
    }

    bool recvStr(string &val)
    {
      int numRead;
      bool success;
      char valBuffer[MAX_MSG_SIZE];
      int ind;
      bool keepReceiving;

      success = true;

      //numRead = read(sock, valBuffer, MAX_MSG_SIZE);
      //Read one char at a time until I get a null..
      ind = 0;
      keepReceiving = true;
      do
      {
        numRead = read(sock, valBuffer + ind, 1);
        if (numRead < 0)
        {
          cout << "ERROR Unable to read from socket: " << numRead
               << " at index: " << ind << endl;
          success = false;
          keepReceiving = false;
        }
        else if(numRead == 0)
        {
          //Do nothing, still waiting..
        }
        else if (numRead == 1)
        {
          if (valBuffer[ind] == 0)
          {
            //Got a null byte, time to stop..
            keepReceiving = false;
          }
          ind++;
        }
        else
        {
          cout << "ERROR Only requested 1 byte, but got: " << numRead << endl;
          success = false;
          keepReceiving = false;
        }
      } while (keepReceiving);

      val = valBuffer;

      return success;
    }
};

#endif // _SOCKET_H_
