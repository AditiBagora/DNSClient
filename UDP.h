#ifndef UDP_H_INCLUDED
#define UDP_H_INCLUDED
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<iostream>
//namespace udp;
using namespace std;
class UDP
{
  public:
   string ip;
   uint16_t port;
   int socketFd;
   char rcvDataBuf[65536];
   struct sockaddr_in destination;
   void SetIp(string ip);
   void SetPort(int port);
   void SendPkt(char* buf,int size_pkt);
   void RecevePkt();
    UDP()
    {
        CreateSocket();
        SetIp("8.8.8.8");
        SetPort(53);
        memset(&rcvDataBuf, 0, 65536);
    }
    void CreateSocket()
    {
     socketFd = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP); //UDP packet for DNS queries
    }
   };
#endif // UDP_H_INCLUDED
