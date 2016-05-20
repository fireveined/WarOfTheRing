#ifndef CSINGLETON_H
#define CSINGLETON_H



template <typename T>
class CSingleton
{
public:

    static T & GetInstance()
    {
        static T Instance;
        return Instance;
    }
};


/* aby utworzyc klase singleton wystarczy napisac taka konstrukcje:


class Cos : public CSingleton<Cos>
{

  public:
  void Foo(){};
};

Cos::GetInstance().Foo();
*/


#endif // CSINGLETON_H
