#include <iostream>
#include "UDP.h"
#include "DnsClient.h"
#include<string>
using namespace std;

int main()
{
    UDP sckt;unsigned char hostname[100];

    sckt.SetIp("192.168.36.53");
    sckt.SetPort(53);

    cout<<"Enter hostname"<<endl;
    cin>> hostname;

    DNSClient dnsclient;
    char* pkt= dnsclient.GetPktTosend(hostname);
    sckt.SendPkt(pkt,dnsclient.size_pkt);
    sckt.RecevePkt();
    dnsclient.ParseResponse(sckt.rcvDataBuf);
}
