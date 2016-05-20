#include "MySql.h"


MYSQL *SqlConn; // wskaŸnik na obiekt/uchwyt po³¹czenia

MYSQL_RES* SqlRes; // dane odebrane

MYSQL_ROW  SqlRow; // pojedynczy wiersz




int MySqlInit()
{
     SqlConn = mysql_init (NULL); // allokuje, inicializuje i zwraca nowy obiekt(uchwyt) po³¹czenia


     if (

          mysql_real_connect ( // nawi¹zuje po³aczenie z baz¹ danych, w razie problemów zwraca b³êdy (false)

               SqlConn, // wska¿nik na obiekt

               "localhost", // nazwa hosta do ktorego chcemy siê pod³¹czyæ (localhost == 127.0.0.1)

               "root", // nazwa uzytkownika

               "", // haslo do bazy

               "eworld", // nazwa bazy do ktorej pragniemy nawiazac polaczenie

               0, // port (0 oznacza uzycie domyslnego)

               NULL, // socket (brak)

               0) // flagi (brak)

          ==NULL)
          return -1;


     return 0;
}



int SelectQuery(std::string Zap)
{
     int result =mysql_real_query(SqlConn,(char*)Zap.c_str(),Zap.length()); // tworzymy zapytanie

     int myerr=mysql_errno(SqlConn);

     if (myerr>0) return -1;

     SqlRes = mysql_store_result(SqlConn); // pobieramy wynik poprzedniego zapytania


     if (mysql_num_rows(SqlRes)>0) {
          // Jesli res zawiera jakieœ wpisy

         SqlRow = mysql_fetch_row(SqlRes);
          return 1;
     } else
          return 886656;


}

int UpdateQuery(std::string Zap)
{
     mysql_query(SqlConn,(char*)Zap.c_str());
}
