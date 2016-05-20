#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED






#include "Common.h"
#include <fstream>

#define NOT_FOUND string::npos
#define POS_END string::npos

class CTokenizer
{

private:
    char* WS_SET;
    char* BR_SET;

    string bufor, cword, err_str;
    unsigned int pos;
    float param;

public:

    CTokenizer()
    {
        WS_SET = " \t\r\n";
        BR_SET = "\r\n";
        pos=0;
    }

    CTokenizer(const string &buf)
    {
        WS_SET = " \t\r\n";
        BR_SET = "\r\n";
        bufor=buf;
        pos=0;
    }

    void Reset(const string&buf)
    {
        bufor=buf;
        pos=0;

    }


    void SetWS_SET(const string& buf)
    {
        WS_SET   = (char*)buf.c_str();
    }

    bool ParseToken(); // pobiera z tekstu kolejne slowo
    bool ParseParam(); // pobiera z tekstu kolejne parametr

    string GetToken(bool parse=1); // zwraca ostatnio pobrane slowo


    float GetParam(bool parse=1 ); // zwraca ostatnio pobrany parametr

    void TokenizeFile(const string&str) // wrzuctuje plik do tokenizera
    {
        fstream plik(str.c_str());
        char c;
        if(plik.good())
            while (true)
            {
                c = plik.get();
                if (plik.eof()) break;
                bufor += c;
            }
        plik.close();
        pos=0;
    }




};

#endif // TOKENIZER_H_INCLUDED
