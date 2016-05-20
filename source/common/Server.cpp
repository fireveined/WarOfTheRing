#include "Server.h"

#include <string>
#include <iostream>
#include <vector>






cserver::cserver(unsigned short port)
{
   /* start server */
   sockaddr_in server_info;
   server_info.sin_family=AF_INET;
   server_info.sin_port=htons(port);
   server_info.sin_addr.s_addr=INADDR_ANY;
   bind(s,(sockaddr*) &server_info,sizeof(server_info));
   listen(s,SOMAXCONN);
   /* start server */

   /* init buffer */

   /* init buffer */
}

cserver::~cserver()
{

}

void cserver::write_packet(int n,CStream packet)
{
   int bytes= send(Connections[n].Connection.get_s(), packet.GetBuffer(), packet.GetOut(), 0);

}

int cserver::update()
{
   int i;

   /* clear FD_SET */
   FD_ZERO(&read_sockets);

   /* clear FD_SET */

   /* for connection requests */
   FD_SET(s,&read_sockets);
   /* for connection requests */

   /* highest file descriptor */
   int hfd=s;

   if (select(hfd+1,&read_sockets,0,0,&delay)>0)
   {

      if (FD_ISSET(s,&read_sockets))
      {


       //  if (clients<MAX_CLIENTS)
         {
      std::cout<<"Nowy Gracz! \n";
       sCon con;
       for(int a=0;a<Connections.size();a++)
       if(Connections[a].Dead)
       {


            Connections[a]=con;
            Connections[a].Connection.create(accept(s,0,0),1);


           return a;
 }

 Connections.push_back(con);

            Connections[Connections.size()-1].Connection.create(accept(s,0,0),1);
        return Connections.size()-1;

            /* create new connection and send new id to server */
         }

      }
      /* accept/reject new connection */
   }
  return -1;
}

int cserver::read_packet(CStream* stream)
{
  for(int a=0;a<Connections.size();a++)Connections[a].IsMsg=0;
   /* id */
   int n=0;
   /* id */
 /* clear FD_SET */
   FD_ZERO(&read_sockets);

   FD_SET(s,&read_sockets);

   int hfd=s;
   /* add sockets to FD_SET and check for highest file descriptor */
   for (int i=0;i<Connections.size();i++)
{
      FD_SET(Connections[i].Connection.get_s(),&read_sockets);
      if (Connections[i].Connection.get_s()>hfd) hfd=Connections[i].Connection.get_s();
}
   /* add sockets to FD_SET and check for highest file descriptor */

   if (select(hfd+1,&read_sockets,0,0,&delay)>0)
   {
      /* read data and remove disconnected connections */
      for (int i=0;i<Connections.size();i++)
      if ( (FD_ISSET(Connections[i].Connection.get_s(),&read_sockets)))
      {
         char buffer[1122];
         int bytes=recv(Connections[i].Connection.get_s(),buffer,1122,0);
         if ((bytes>0))
         {
            buffer[bytes]=0;
            memcpy (Connections[i].Msg.GetBuffer(), buffer, bytes);

            Connections[i].Msg.Reset();
            std::cout<<bytes;
            Connections[i].IsMsg=bytes;
         }



      }
}
   /* return id */

   /* return id */
}
