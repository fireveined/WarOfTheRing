#ifndef CCONFIGFILE_H
#define CCONFIGFILE_H

#include "Common.h"
#include <fstream>
#include <vector>

class sConfig
{
private:
    string name;
    string param;

public:

    void SetName(const string& str)
    {
        name=str;
    }
    void SetParam(int par)
    {
        param=IntToStr(par);
    }
    void SetParam(const string&par)
    {
        param=par;
    }
    int GetParam()
    {
        return StrToInt(param);
    }
    const string& GetParamStr()
    {
        return param;
    }
    const string& GetName()
    {
        return name;
    }

    sConfig(const string& str, int par)
    {
        name=str;
        param=IntToStr(par);
    }
    sConfig(const string& str, const string& par)
    {
        name=str;
        param=par;
    }
    sConfig() {}
};

class CConfigFile
{

private:

    fstream File;
    string FileName;
    vector<sConfig> Configs;

public:


    CConfigFile() {}
    CConfigFile(const string& name);
    void LoadConfig(const string& name);  // wczytuje plik z dysku
    sConfig* GetConfig(const string& name);
    void AddConfig(const sConfig&con);
    void SaveConfig(const string& name); //zapisuje plik na dysk




};

#endif // CCONFIGFILE_H
