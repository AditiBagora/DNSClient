#include"UDP.h"

using namespace std;
void UDP:: SetIp(string ip1)
{
      ip=ip1;
}
void UDP:: SetPort(int port)
{
    port=port;
}

void UDP:: SendPkt(char* buf,int size_pkt)
{
       destination.sin_family = AF_INET;
       destination.sin_port = htons(53);
       inet_pton(AF_INET, ip.c_str(), &(destination.sin_addr));
       memset(&(destination.sin_zero), '\0', 8);
       cout<<"Sending Query...";
       int bytesend=sendto(socketFd,buf,size_pkt,0,(struct sockaddr*)&destination,sizeof(sockaddr_in));
       if(bytesend<0)
       {
         cout<<"sendto failed";

       }
      cout<<"Done"<<endl;
}
void UDP::RecevePkt()
{
       socklen_t sinSize = sizeof(struct sockaddr_in);
       cout<<"Receiving response...";
       if(recvfrom (socketFd,(char *)&rcvDataBuf , 65536 , 0 , (struct sockaddr*)&destination , &sinSize ) < 0)
       {
          cout<<"recvfrom failed";
       }
       cout<<"Done"<<endl;
     }


