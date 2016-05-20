#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#include "Common.h"
#include <fstream>
#include <iostream>

class CStream
{

private:

    char* Buffer;
    uint4 In,Out, Len;

public:

    CStream() {}
    CStream(uint4 len);

    void CreateStream(uint4 len);
    void SetIn(uint4 in)
    {
        In=in;
    }
    void SetOut(uint4 out)
    {
        Out=out;
    }
    char* GetBuffer()
    {
        return Buffer;
    }
    void SetBuffer(char* buf)
    {

      // strcpy(Buffer,buf);
        In=0;
        Out=0;
    }
    uint4 GetLength()
    {
        return Out;
    }
    void Reset()
    {
        In=0;
        Out=0;
    }

uint4 GetOut()
{
    return Out;
}

uint4 GetIn()
{
    return In;
}

void AddIn(int i)
{
    In+=i;

}

void AddOut(int i)
{
    Out+=i;

}




    void SaveFile(const string&str)   //zapisuje  strumien do pliku
    {
        fstream plik(str.c_str(),ios::trunc | ios::out | ios::binary);
        plik.write (Buffer,Out);
        plik.close();

    }


    void LoadFile(const string&str) // wczytuje strumien z pliku
    {
        fstream plik(str.c_str(),ios::binary | ios::in);

       plik.read (Buffer,Len);

        plik.close();
        In=0;
        Out=0;

    } 

	 


};



    CStream& operator>> (CStream &str,uint1 &i);
    CStream& operator>> (CStream &str,uint2 &i);
    CStream& operator>> (CStream &str,uint4 &i);
    CStream& operator>> (CStream &str,int1 &i);
    CStream& operator>> (CStream &str,int2 &i);
    CStream& operator>> (CStream &str,int4 &i);

    CStream& operator>> (CStream &str,float &i);
    CStream& operator>> (CStream &str,double &i);


    CStream& operator>> (CStream &str,string &i);




    CStream& operator<< (CStream &str,uint1 i);
    CStream& operator<< (CStream &str,uint2 i);
    CStream& operator<< (CStream &str,uint4 i);
    CStream& operator<< (CStream &str,int1 i);
    CStream& operator<< (CStream &str,int2 i);
    CStream& operator<< (CStream &str,int4 i);

    CStream& operator<< (CStream &str,float i);
    CStream& operator<< (CStream &str,double i);


    CStream& operator<< (CStream &str,string i);
#endif // STREAM_H_INCLUDED

