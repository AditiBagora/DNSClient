#include "DnsClient.h"

char* DNSClient::GetPktTosend(unsigned char *  hostname){
   CreateDefaultDnsPkt();
   CreateQuery(hostname);
   return (char*)&buf;
}

void DNSClient::CreateDefaultDnsPkt()
{
    CreateDefaultHeader();
    size_pkt=sizeof(struct DNS_HEADER);
}
void DNSClient::CreateDefaultHeader()
{
    header = (struct DNS_HEADER *)&buf;

    header->id = (unsigned short) htons(getpid());
    header->qr = 0;
    header->opcode = 0;
    header->aa = 0;
    header->tc = 0;
    header->rd = 1;
    header->ra = 0;
    header->z = 0;
    header->ad = 0;
    header->cd = 0;
    header->rcode = 0;
    header->q_count = htons(1);
    header->ans_count = 0;
    header->auth_count = 0;
    header->add_count = 0;
}

void DNSClient::CreateQuery(unsigned char *  hostname)
{
    unsigned char *qname;
    struct QUESTION* qinfo;
    qname=(unsigned char*)&buf[sizeof(struct DNS_HEADER)];
    ChangetoDnsNameFormat(qname , hostname);
    qinfo =(struct QUESTION*)&buf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname)+1)];
    qinfo->qtype = htons( T_A );
    qinfo->qclass = htons(1);
    size_pkt+=strlen((const char*)qname) + 1+sizeof(struct QUESTION);
}

void DNSClient::ParseResponse(char buf[65536])
{
    cout<<"Parsing Response"<<endl;
    header = (struct DNS_HEADER *)buf;
    uint8_t *start_of_name = (uint8_t *) (buf + sizeof (struct DNS_HEADER));
    uint8_t total = 0;
    uint8_t *field_length = start_of_name;
    while (*field_length != 0)
    {
        total += *field_length + 1;
       *field_length = '.';
       field_length = start_of_name + total;
     }
    dns_response* records = (dns_response *) (field_length + 5);
    cout<<"Response contains "<< ntohs(header->ans_count)<<" Answer"<<endl;
    for (int i = 0; i < ntohs(header->ans_count); i++)
    {
       cout<<"TYPE:"<<ntohs (records[i].type)<<endl;
       cout<<"CLASS:"<<ntohs (records[i].rr_class)<<endl;
       cout<<"TTL:"<<ntohl (records[i].ttl)<<endl;
       cout<<"IPv4:"<<inet_ntoa (records[i].addr)<<endl;
     }
   return;
}
