#include "Connection.h"

cconnection::cconnection()
{
   id=-1;
}

SOCKET cconnection::get_s()
{
   return s;
}

int cconnection::get_id()
{
   return id;
}

char* cconnection::get_rb()
{
   return rb;
}

char* cconnection::get_sb()
{
   return sb;
}

void cconnection::create(SOCKET as,int n)
{
   s=as;
   id=n;
   rb[0]=0;
   sb[0]=0;
}

void cconnection::reset()
{
   closesocket(s);
   id=-1;
}

void cconnection::destroy()
{
   closesocket(s);
}
