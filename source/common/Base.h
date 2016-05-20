#ifndef CBASE_H
#define CBASE_H
   #include <string>
#ifdef _WIN32
   #include <winsock.h>
#else
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <arpa/inet.h>
   #include <sys/select.h>
   #include <unistd.h>
   #define SOCKET int
   #define closesocket close
#endif

#include "Stream.h"

class cbase
{
 public:
   SOCKET s;
   fd_set read_sockets,write_sockets;
   timeval delay;
     sockaddr_in server_info;


   cbase();
   virtual ~cbase();
   virtual bool connected();
   virtual void write_packet(int n,CStream stream)=0;
   virtual int update()=0;
   virtual int read_packet(CStream* stream)=0;
};


#endif
