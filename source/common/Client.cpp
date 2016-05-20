#include "Client.h"
#include "Stream.h"
std::string Packet;

cclient::cclient(char* ip,unsigned short port)
{
   /* connect to server */
   sockaddr_in server_info;
   server_info.sin_family=AF_INET;
   server_info.sin_port=htons(port);
   server_info.sin_addr.s_addr=inet_addr(ip);
   connection=connect(s,(sockaddr*) &server_info,sizeof(server_info))==0;
   /* connect to server */

   /* init buffers */
   rb[0]=0;
   sb[0]=0;
   /* init buffers */


}

bool cclient::connected()
{
   return connection;
}

void cclient::write_packet(int n,CStream str)
{
send(s, str.GetBuffer(),str.GetLength(), 0);



}

int cclient::update()
{
   /* clear FD_SET */
   FD_ZERO(&read_sockets);
   FD_ZERO(&write_sockets);
   /* clear FD_SET */

   /* add socket to FD_SET */
   FD_SET(s,&read_sockets);
   FD_SET(s,&write_sockets);
   /* add socket to FD_SET */

   /* read and write data */
   if (select(s+1,&read_sockets,&write_sockets,0,&delay)>0)
   {
      /* read data and disconnect */
      if (FD_ISSET(s,&read_sockets))
      {
         char buffer[1025];
         int bytes=recv(s,buffer,1024,0);
         if ((bytes>0) && (strlen(rb)+bytes<MAX_BUFFER))
         {
            buffer[bytes]=0;
            strcat(rb,buffer);
         }
         else
         {
            closesocket(s);
            connection=0;
         }
      }
      /* read data and disconnect */

      /* send data and remove it from the sendbuffer */
      if (FD_ISSET(s,&write_sockets))
      {
         int bytes=send(s,sb,strlen(sb),0);
         strcpy(sb,sb+bytes);
      }
      /* send data and remove it from the sendbuffer */
   }
   /* read and write data */
   return 1;
}

int cclient::read_packet(CStream* str)
{
   /* id */
   int n=0;
   /* id */
 /* clear FD_SET */
   FD_ZERO(&read_sockets);

   FD_SET(s,&read_sockets);

   int hfd=s;

   if (select(hfd+1,&read_sockets,0,0,&delay)>0)
   {
          if (FD_ISSET(s,&read_sockets))
      {
         char buffer[1200];
         int bytes=recv(s,buffer,1200,0);
         if ((bytes>0))
         {
            buffer[bytes]=0;
           str->SetBuffer(buffer);

            n=bytes;


         }
         else
         {
            closesocket(s);
            connection=0;
         }
      }

      }
      return n;
}
