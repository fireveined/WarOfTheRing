#ifndef CCONNECTION_H
#define CCONNECTION_H

#define MAX_BUFFER 32768

#ifdef _WIN32
   #include <winsock.h>
#else
   #include <unistd.h>
   #define SOCKET int
   #define closesocket close
#endif

#include <string>
class cconnection
{
 private:
   SOCKET s;
   int id;
   char rb[MAX_BUFFER];
   char sb[MAX_BUFFER];

 public:
   cconnection();
   SOCKET get_s();
   int get_id();
   char* get_rb();
   char* get_sb();
   void create(SOCKET as,int n);
   void reset();
   void destroy();
std::string GetIP()
   {
       sockaddr_in ip;
       int sf=sizeof(struct sockaddr);
   getpeername(s, (struct sockaddr*)&ip, &sf);
   std::string a1 = inet_ntoa(ip.sin_addr);
   return a1;
   }

};

#endif
