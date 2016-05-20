#include "Timer.h"
#include <time.h>

CTimer::CTimer()
{
    m_Interval = 1;
    Reset();
    isLoop=0;
}

CTimer::CTimer(int Interval)
{
    SetInterval(Interval);
    isLoop=0;
}

CTimer::~CTimer()
{
}

void CTimer::SetInterval(int Interval)
{
    m_Interval = Interval;
    Reset();
}

void CTimer::Reset()
{
    m_LastTime = clock();
}

bool CTimer::TimeUp()
{
    if( (clock() - m_LastTime) > m_Interval )
    {
        return true;
    }

    return false;
}

int CTimer::GetTicks()
{
    int ticks = clock() - m_LastTime;
    return ticks;
}

double CTimer::fTime, CTimer::fNewTime, CTimer::dt;
float CTimer::fFPS, CTimer::fFPSTime;
unsigned CTimer::uFrames;

void CTimer::FPS()
{


    fNewTime = clock() / 1000.0f;
    dt = fNewTime - fTime;
    fTime = fNewTime;


    ++uFrames;
    fFPSTime += dt;

    if (fFPSTime>= 1.0f)
    {

        fFPS = uFrames / fFPSTime;
        uFrames = 0;
        fFPSTime = 0.0f;



    }

}
