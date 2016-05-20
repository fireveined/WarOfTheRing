#include "Logger.h"

CLogger g_Logger;

void CLogger::CreateLogger(const string &file, int flush)
{
    File.open(file.c_str(),ios::trunc | ios::out );
    File<<"<font size=\"7\">Log silnika AddEngineX5 </font> <br>";
    File.close();

    FileName=file;
    iFlush=flush;
    ActFlush=0;

}



void CLogger::AddToken(int type, const string &token)
{
    Tokens.push_back(sToken(type,token));

}


void CLogger::DeleteToken(int type)
{
    for (uint2 a=0; a<Tokens.size(); a++)
        if (Tokens[a].type==a)Tokens.erase(Tokens.begin()+a);

}

void CLogger::AddLog(const string &log, eLogType type, int token)
{
    string Token;
    for (uint2 a=0; a<Tokens.size(); a++)
        if (Tokens[a].type==token)Token+=Tokens[a].token;

    static string info[]= {"<b>Informacja:</b> ","<font color=\"red\"><b>Ostrze¿enie</b></font>: ","<font color=\"jmaroon\"><b>B³¹d</b></font>: "};
    Logs.push_back(info[type]+"<font color=\"gray\">"+Token+"</font>"+log+"<br>");

    ActFlush++;
    if (ActFlush>=iFlush)Flush();

}


void CLogger::Flush()
{
    File.open(FileName.c_str(),ios::app | ios::out);

    for (uint2 a=Logs.size()-ActFlush; a<Logs.size(); a++)
        File<<Logs[a];

    ActFlush=0;

    File.close();

}

