#include "Tokenizer.h"


  string CTokenizer::GetToken(bool parse) // zwraca ostatnio pobrane slowo
    {	if(parse)ParseToken();
        return cword;
    }

    float CTokenizer::GetParam(bool parse ) // zwraca ostatnio pobrany parametr
    {
		if(parse)ParseParam();
        return param;
    }


bool CTokenizer::ParseToken()
{


    unsigned int tmp_pos, tmp_pos2;

    tmp_pos = bufor.find_first_not_of(WS_SET, pos);
    if(tmp_pos == 0xFFFFFFFF)
    {
        cword.clear();
        pos = POS_END;
        return false;
    }
    tmp_pos2 = bufor.find_first_of(WS_SET, tmp_pos);
    if(tmp_pos2 == NOT_FOUND)
    {
        pos = bufor.length()-1;
        cword = bufor.substr(tmp_pos, bufor.length()-tmp_pos);
    }
    else
    {
        pos = tmp_pos2;
        cword = bufor.substr(tmp_pos, tmp_pos2-tmp_pos);
    }

    if(pos==bufor.length() || tmp_pos==bufor.length() || tmp_pos2==bufor.length()) return false;
    return true;


}


bool CTokenizer::ParseParam()
{

    unsigned int tmp_pos, tmp_pos2;
    string s_number;

    tmp_pos = bufor.find_first_not_of(WS_SET, pos);
    if(tmp_pos == NOT_FOUND)
    {
        param = 0;
        pos = POS_END;
        return false;
    }
    tmp_pos2 = bufor.find_first_of(WS_SET, tmp_pos);
    cword.clear();
    if(tmp_pos2 == NOT_FOUND)
    {
        tmp_pos2 = bufor.find_last_not_of(WS_SET, tmp_pos);
        if(tmp_pos2 == tmp_pos)
        {
            s_number = bufor[tmp_pos];
        }
        pos = tmp_pos2;
    }
    if(s_number.empty())
    {
        s_number = bufor.substr(tmp_pos, tmp_pos2-tmp_pos);
        pos = tmp_pos2;
    }

    param = StrToFloat(s_number);

    return true;


}
