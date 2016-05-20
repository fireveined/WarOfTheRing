#include "Base.h"

cbase::cbase()
{
   #ifdef _WIN32
   /* start winsock 1.1 */
   WSAData winsock_info;
   WSAStartup(MAKEWORD(1,1),&winsock_info);
   /* start winsock 1.1 */
   #endif

   /* create socket */
   s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   /* create socket */

   /* init delay */
   delay.tv_sec=delay.tv_usec=0;
   /* init delay */
}

cbase::~cbase()
{
   /* close socket */
   closesocket(s);
   /* close socket */

   #ifdef _WIN32
   /* exit winsock */
   WSACleanup();
   /* exit winsock */
   #endif
}

bool cbase::connected()
{
   /* virtual */
}
