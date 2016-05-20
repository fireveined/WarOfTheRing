#ifndef CCLIENT_H
#define CCLIENT_H

#define MAX_BUFFER 32768

#include <string.h>
#include "Base.h"
#include "Stream.h"

class cclient : public cbase
{
 private:
   char rb[MAX_BUFFER];
   char sb[MAX_BUFFER];
   bool connection;

 public:
   cclient(char* ip,unsigned short port);
   bool connected();
   void write_packet(int n,CStream stream);
   int update();
   int read_packet(CStream* stream);
};

#endif
