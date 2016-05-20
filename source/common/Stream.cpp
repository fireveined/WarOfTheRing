#include "Stream.h"

CStream::CStream(uint4 len)
{
     In=0;
     Out=0;
     Buffer=new char[len];
}


void CStream::CreateStream(uint4 len)
{
     In=0;
     Out=0;
     if (Buffer)
          delete []Buffer;
     Buffer=new char[len];
}






CStream& operator<< (CStream &str,uint1 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(uint1));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,uint2 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(uint2));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,uint4 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(uint4));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,int1 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(i));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,int2 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(i));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,int4 i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(i));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}


CStream& operator<< (CStream &str,float i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(i));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}

CStream& operator<< (CStream &str,double i)
{
     memcpy( str.GetBuffer()+str.GetOut(), &i , sizeof(i) );
     str.AddOut(sizeof(i));
     str.GetBuffer()[str.GetOut()]=0;
     return str;
}




CStream& operator<< (CStream&str,string i)
{

     uint2 le=i.length();
str<<le;


     for (uint4 a=0; a<i.length(); a++) {
         uint1 b= i[a];
         str<<b;


     }

     return str;
}


CStream& operator>> (CStream &str,uint1 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(uint1) );
     str.AddIn(sizeof(uint1));
     return str;
}

CStream& operator>> (CStream &str,uint2 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  2 );
     str.AddIn(2);
     return str;
}

CStream& operator>> (CStream &str,uint4 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}


CStream& operator>> (CStream &str,int1 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}


CStream& operator>> (CStream &str,int2 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}


CStream& operator>> (CStream &str,int4 &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}


CStream& operator>> (CStream &str,float &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}

CStream& operator>> (CStream &str,double &i)
{
     memcpy( &i , str.GetBuffer()+str.GetIn() ,  sizeof(i) );
     str.AddIn(sizeof(i));
     return str;
}





CStream& operator>> (CStream &str,string &i)
{

     uint2 le;
     str>>le;
uint1 c=0;
     for (int a=0; a<le; a++) {

          str>>c;
          i+=c;
     }

     return str;
}


