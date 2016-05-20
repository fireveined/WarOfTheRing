#include "ConfigFile.h"
#include "Tokenizer.h"

CConfigFile::CConfigFile(const string& name)
{

    CTokenizer token;
    token.TokenizeFile(name);

    while (token.ParseToken())
    {
        sConfig conf;
        conf.SetName(token.GetToken());

        token.ParseToken();
        token.ParseToken();
        conf.SetParam(token.GetToken());
        Configs.push_back(conf);
    }


}




sConfig* CConfigFile::GetConfig(const string& name)
{

    for (uint2 a=0; a<Configs.size(); a++)
        if (Configs[a].GetName()==name)return &Configs[a];

    return 0;
}

void CConfigFile::AddConfig(const sConfig&con)
{
    Configs.push_back(con);
}


void CConfigFile::LoadConfig(const string& name)
{

    Configs.clear();

    CTokenizer token(name);

    while (token.ParseToken())
    {
        sConfig conf;
        conf.SetName(token.GetToken());

        token.ParseToken();
        token.ParseToken();
        conf.SetParam(token.GetToken());
        Configs.push_back(conf);
    }

}


void CConfigFile::SaveConfig(const string& name)
{

    File.open(name.c_str(),ios::trunc | ios::out);

    for (uint2 a=0; a<Configs.size(); a++)
        File<<Configs[a].GetName()<<" = "<<Configs[a].GetParamStr()<<"\n";

    File.close();
}
