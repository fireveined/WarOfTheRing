#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

class CTimer
{

    int m_Interval;
    int m_LastTime;
    bool isLoop;
public:

    CTimer();
    CTimer(int Interval);
    ~CTimer();
    void SetInterval(int Interval);
    void Reset();
    bool TimeUp();
    int GetTicks();
    void Loop(bool loop)
    {
        isLoop=loop;
    }
    int GetInterval()
    {
        return m_Interval;
    }

    static double fTime, fNewTime, dt;
    static float fFPS, fFPSTime;
    static unsigned uFrames;

    static void FPS();
};


#endif // TIMER_HPP_INCLUDED
