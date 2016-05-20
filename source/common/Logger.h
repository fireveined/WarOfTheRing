#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "Common.h"
#include <vector>
#include <fstream>

#define TOKEN_SHADER 1
#define TOKEN_GRAFIC 2

enum eLogType
{
    LOG_INFORMATION,
    LOG_WARNING,
    LOG_ERROR
};

struct sToken
{
    int type;
    string token;
    sToken() {}
    sToken(int ty, const string &to)
    {
        type=ty,token=to;
    }
};

class CLogger   // klasa Loggera
{


private:

    fstream File;
    vector<string> Logs;   //log
    string FileName;   //nazwa pliku
    int iFlush;       // max. ilosc zakolejowanych logow do zapisania
    int ActFlush;    // ilosc zakolejowanych logow do zapisania
    vector<sToken> Tokens;


public:

    CLogger() {};
    void CreateLogger(const string &file, int flush=1);
    void AddToken(int type, const string &token); // dodaje token
    void DeleteToken(int type); // usuwa token
    void SetFlush(int flush) // ustawia max. liczbe zakolejowanych logow
    {
        iFlush=flush;
        if (ActFlush>=iFlush)Flush();
    };
    void AddLog(const string &log, eLogType typ=LOG_INFORMATION, int token=-1); // dodaje log
    void Flush(); // zapisuje logi na dysk
    string GetLog() // zwraca log
    {
        string loge;
        for (uint2 a=0; a<Logs.size(); a++)loge+=Logs[a];
        return loge;
    }
};

extern CLogger g_Logger;

#endif // LOGGER_H_INCLUDED
