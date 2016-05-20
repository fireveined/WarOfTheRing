#ifndef CSERVER_H
#define CSERVER_H

#define MAX_CLIENTS 63

#include <vector>
#include <string>
#include "Base.h"
#include "Connection.h"

struct sCon
{

    cconnection Connection;
    CStream Msg;
    int IsMsg;
bool Dead;

    sCon(){Msg.CreateStream(500);IsMsg=0;Dead=0;}
};

class cserver : public cbase
{
    vector<sCon> Connections;

 public:


   cserver(unsigned short port);
   ~cserver();
   void write_packet(int n,CStream stream);
   int update();
   int read_packet(CStream* stream);

   int GetMsg(int id, CStream* str)
   {
       *str=Connections[id].Msg;
       return Connections[id].IsMsg;
   }
   sCon GetCon(int id){return Connections[id];}


   void DeleteClient(int id)
   {
       Connections[id].Dead=1;
   }


};


#endif
