
#ifndef MYSQL_H
#define MYSQL_H



#include "Server.h"
#include <mysql/mysql.h>


extern MYSQL *SqlConn; // wska�nik na obiekt/uchwyt po��czenia

extern MYSQL_RES* SqlRes; // dane odebrane

extern MYSQL_ROW  SqlRow; // pojedynczy wiersz



int MySqlInit();


int SelectQuery(std::string Zap);


int UpdateQuery(std::string Zap);








                         #endif
