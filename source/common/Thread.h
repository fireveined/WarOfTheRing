#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <pthread.h>
#include "Common.h"
#include <vector>


class CMutex
{
private:
    pthread_mutex_t Mutex;
    string Name;

public:
    CMutex()
    {
        Mutex=PTHREAD_MUTEX_INITIALIZER;
    }
    CMutex(const string& name)
    {
        Name=name;
        Mutex=PTHREAD_MUTEX_INITIALIZER;
    }
    void Lock()
    {
        pthread_mutex_lock(&Mutex);
    }
    void Unlock()
    {
        pthread_mutex_unlock(&Mutex);
    }
    const string& GetName()
    {
        return Name;
    }

};




void LockMutex(const string& name);
void UnlockMutex(const string& name);

void* DefaultThread( void* arg);

class CThread
{

private:
    pthread_t Thread;
    void* (*Func)( void* );
    void* Param;
    bool Created;

public:

    CThread() {}
    CThread(void* (*func)( void* ), void* par);
    void Create(void* (*func)( void* ), void*  par);

    void Delete();

};

#endif // THREAD_H_INCLUDED
