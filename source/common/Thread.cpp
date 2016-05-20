#include "Thread.h"

CThread::CThread(void* (*func)( void* ), void* par)
{
    Func=func;
    Param=par;
    pthread_create( &Thread, NULL, Func, Param );
    Created=1;
}


void CThread::Create(void* (*func)( void* ), void* par)
{
    if (!Created)
    {
        Func=func;
        Param=par;
        pthread_create( &Thread, NULL, Func, par );
        Created=1;
    }

}


void CThread::Delete()
{
    pthread_cancel(Thread);
    Created=0;
}



vector<CMutex> Mutexes;


void LockMutex(const string& name)
{
    for (uint2 a=0; a<Mutexes.size(); a++)
        if (Mutexes[a].GetName()==name)
        {
            Mutexes[a].Lock();
            return;
        }

    Mutexes.push_back(CMutex(name));
    Mutexes[Mutexes.size()-1].Lock();
}


void UnlockMutex(const string& name)
{
    for (uint2 a=0; a<Mutexes.size(); a++)
        if (Mutexes[a].GetName()==name)
        {
            Mutexes[a].Unlock();
            return;
        }

}

void* DefaultThread( void* arg)
{
    return 0;
}
