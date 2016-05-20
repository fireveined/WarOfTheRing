#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <string>
#include <cstring>

typedef char int1;
typedef short int int2;
typedef int int4;
typedef long long int int8;


typedef unsigned char uint1;
typedef unsigned short int uint2;
typedef unsigned int uint4;
typedef unsigned long long int uint8;

using namespace std;


string IntToStr(int l);
int StrToInt(const string &s);
string FloatToStr(float l);
float StrToFloat(const string &s);

string ExtractFilename( const string& path );


class CColor
{

    float R,G,B,A;
public:
    CColor() {}

    CColor(int r, int g, int b, int a=255);
    CColor(uint1 r, uint1 g, uint1 b, uint1 a=255);
    CColor(float r, float g, float b, float a=1.0f);


// char GetR(){return R;}
//  char GetG(){return G;}
//  char GetB(){return B;}
//  char GetA(){return A;}

    float GetR()
    {
        return R;
    }
    float GetG()
    {
        return G;
    }
    float GetB()
    {
        return B;
    }
    float GetA()
    {
        return A;
    }

    void SetR(float r)
    {
        R=r;
    }
    void SetG(float r)
    {
        G=r;
    }
    void SetB(float r)
    {
        B=r;
    }
    void SetA(float r)
    {
        A=r;
    }

//  void SetR(float r){R=(uint1)(r*255);}
//  void SetG(float r){G=(uint1)(r*255);}
//  void SetB(float r){B=(uint1)(r*255);}
//   void SetA(float r){A=(uint1)(r*255);}

    CColor GetBackColor()
    {
        return CColor(1.0f-R,1.0f-G,1.0f-B);
    }



    void SetColor(uint1 r, uint1 g, uint1 b, uint1 a=255)
    {
        R=(float)r/255;
        G=(float)g/255;
        B=(float)b/255;
        A=(float)a/255;
    }
    void SetColor(float r, float g, float b, float a=1.0)
    {
        R=r;
        G=g;
        B=b;
        A=a;
    }
};

		struct sPoint
{
int X,Y;
sPoint(){}
sPoint(int xx, int yy){X=xx,Y=yy;}
};

#endif // COMMON_H_INCLUDED
