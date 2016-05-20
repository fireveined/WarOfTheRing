#include "Common.h"
#include <sstream>

string IntToStr(int n)
{
    string tmp;
    if (n < 0)
    {
        tmp = "-";
        n = -n;
    }
    if (n > 9)
        tmp += IntToStr(n / 10);
    tmp += n % 10 + 48;
    return tmp;
}


string FloatToStr(float i)
{
    ostringstream ss;
    ss << i;
    return ss.str();
}



int StrToInt(const string &s)
{
    int tmp = 0, i = 0;
    bool m = false;
    if (s[0] == '-')
    {
        m = true;
        i++;
    }
    for (; i < s.size(); i++)
        tmp = 10 * tmp + s[i] - 48;
    return m ? -tmp : tmp;
}



float StrToFloat(const string &s)
{
    float i;
    istringstream iss(s);
    iss >> i;
    return i;

}

string ExtractFilename( const string& path )
{
    return path.substr( path.find_last_of( '\\' ) +1 );
}


CColor::CColor(uint1 r, uint1 g, uint1 b, uint1 a)
{
    R=(float)r/255;
    G=(float)g/255;
    B=(float)b/255;
    A=(float)a/255;
}
CColor::CColor(int r, int g, int b, int a)
{
    R=(float)r/255;
    G=(float)g/255;
    B=(float)b/255;
    A=(float)a/255;
}
CColor::CColor(float r, float g, float b, float a)
{
    R=r;
    G=g;
    B=b;
    A=a;
}
